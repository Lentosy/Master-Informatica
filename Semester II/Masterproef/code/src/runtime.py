
import sys
import os
import constants
import ctypes

os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # surpress pygame output
import pygame


from pykinect2 import PyKinectV2
from pykinect2.PyKinectV2 import FrameSourceTypes_Color, FrameSourceTypes_Depth, FrameSourceTypes_Body, TrackingState_Tracked, TrackingState_NotTracked, TrackingState_Inferred
from pykinect2 import PyKinectRuntime

class Runtime():
    def __init__(self, fps):
        pygame.init()     
        pygame.display.set_caption("KinectV2 for Windows")
        
        # get info about the current graphical environment (mostly the whole screen)
        displayInfo = pygame.display.Info()
        width = displayInfo.current_w >> 1 # bit shift to the right so we dont take the full screen
        height = displayInfo.current_h >> 1
        self.screen = pygame.display.set_mode((width, height), # resolution
                                              pygame.HWSURFACE | pygame.DOUBLEBUF | pygame.RESIZABLE | pygame.NOFRAME)

        # Loop until the user clicks the close button.
        self.done = False
        # Used to manage how fast the screen updates
        self.clock = pygame.time.Clock()
        # Kinect runtime object 
        self.kinect = PyKinectRuntime.PyKinectRuntime(FrameSourceTypes_Color | FrameSourceTypes_Depth | FrameSourceTypes_Body)
        # back buffer surface for getting Kinect color frames, 32bit color, width and height equal to the Kinect color frame size
        self.frame_surface = pygame.Surface((self.kinect.color_frame_desc.Width, self.kinect.color_frame_desc.Height), 0, 32)
        # skeleton data
        self.skeletons = None
        # frames per second to run at
        self.fps = fps
   
    def extract_body_information(self, body):
        #TODO: PyKinectV2 does not offer the 3D camera coordinates, only a mapping of those onto the color or depth space. 
        # -> Try to find out how many pixels equals one meter
        joints = body.joints  
        orientations = body.joint_orientations
        
        depth_points = self.kinect.body_joints_to_depth_space(joints)
        depth_list = self.kinect.get_last_depth_frame()

        coordinates = []
        quaternions = []
        
        for j in range(0, len(constants.JOINTS)):
            try:
                x = depth_points[j].x                    
                y = depth_points[j].y
                c = int(y) * 512 + int(x) # depth index to be used in depth_list
                if(c > len(depth_list) or (x < 0 and y < 0)):
                    z = -1 # joint is not in view, so no depth data exists
                else:
                    z = depth_list[c]
                coordinates.extend([x, y, z])
                quaternions.extend([orientations[j].Orientation.x, orientations[j].Orientation.y, orientations[j].Orientation.z, orientations[j].Orientation.w])
            except: # error ocurred, treat joint as invalid
                (x, y, z) = (-1, -1, -1)
        return [';'.join(str(c) for c in coordinates), ';'.join(str(q) for q in quaternions)]

    def is_joint_tracked(self, joint):
        jointState = joint.TrackingState
        return not jointState == TrackingState_NotTracked and not jointState == TrackingState_Inferred

    # This function draws a straight line segment starting from joint0 and ending in joint1
    def draw_body_bone(self, joints, jointPoints, color, joint0, joint1):
        if(not self.is_joint_tracked(joints[joint0]) and not self.is_joint_tracked(joints[joint1])):
            return
        # at least one joint is tracked. This will produce a line that goes outside the frame
        start = (jointPoints[joint0].x, jointPoints[joint0].y)
        end = (jointPoints[joint1].x, jointPoints[joint1].y)
        try:
            pygame.draw.line(self.frame_surface, color, start, end, constants.SKELETON_LINE_THICKNESS)
        except Exception as e: # sometimes coordinates can be (-inf, -inf)
            pass

    # This function draws a circle at a joint location
    def draw_joint_circle(self, joints, jointPoints, color, joint):
        if(not self.is_joint_tracked(joints[joint])):
            return
        center = (int(jointPoints[joint].x), int(jointPoints[joint].y))
        pygame.draw.circle(self.frame_surface, color, center, constants.SKELETON_CIRCLE_RADIUS, 0)
    
    def draw_body(self, joints, jointPoints, color):
        for i in range(len(constants.JOINT_CONNECTIONS)):
            self.draw_body_bone(joints, jointPoints, color, constants.JOINT_CONNECTIONS[i][0], constants.JOINT_CONNECTIONS[i][1])
            # optimalisation: JOINT_CONNECTIONS list (from constants.py) contains  an equal amount of elements as the JOINTS list. So it can be put in one loop
            self.draw_joint_circle(joints, jointPoints, color, constants.JOINTS[i]) 
    
    def draw_color_frame(self, frame, target_surface):
        target_surface.lock()
        address = self.kinect.surface_as_array(target_surface.get_buffer())
        ctypes.memmove(address, frame.ctypes.data, frame.size)
        del address
        target_surface.unlock()
    
    def copy_back_buffer(self):
            # --- copy back buffer surface pixels to the screen, resize it if needed and keep aspect ratio
            # --- (screen size may be different from Kinect's color frame size) 
            h_to_w = float(self.frame_surface.get_height()) / self.frame_surface.get_width()
            target_height = int(h_to_w * self.screen.get_width())
            surface_to_draw = pygame.transform.scale(self.frame_surface, (self.screen.get_width(), target_height));
            self.screen.blit(surface_to_draw, (0,0))
            surface_to_draw = None
            pygame.display.update()
    
    def exit(self):
        # Close the Kinect sensor, close the window and quit.
        self.kinect.close()
        pygame.quit()

    def run(self): # general use case for the run method: iterate over generated events and then execute the logic for a single run
        while not self.done:
            for event in pygame.event.get():
                self.handle_event(event)
            self.handle_logic()
            self.copy_back_buffer()
            self.clock.tick(self.fps)
        self.exit()

    def handle_event(self, event):
        if event.type == pygame.QUIT: # If user clicked close
            self.done = True # Flag that we are done so we exit this loop
        elif event.type == pygame.VIDEORESIZE: # window resized
            self.screen = pygame.display.set_mode(event.dict['size'], 
                                       pygame.HWSURFACE|pygame.DOUBLEBUF|pygame.RESIZABLE, 32)
        else:
            self.handle_custom_event(event)

    def handle_custom_event(self, event):
        raise NotImplementedError("This is an abstract method. Implement this in a subclass")
    
    def handle_logic(self):
        raise NotImplementedError("This is an abstract method. Implement this in a subclass")

class DefaultRuntime(Runtime):
    def __init__(self):
        print("Starting Default Runtime...")
        Runtime.__init__(self, constants.DEFAULT_FPS)
    
    def handle_custom_event(self, event):
        pass
    
    def handle_logic(self):
        if self.kinect.has_new_color_frame():
                frame = self.kinect.get_last_color_frame()
                self.draw_color_frame(frame, self.frame_surface)
                frame = None
        
        if self.kinect.has_new_body_frame(): 
            self.skeletons = self.kinect.get_last_body_frame()
        
        if self.skeletons is not None: 
            for body in self.skeletons.bodies:
                if body.is_tracked: 
                    joint_points = self.kinect.body_joints_to_color_space(body.joints)
                    self.draw_body(body.joints, joint_points, constants.SKELETON_COLORS[0])                    
            
class DebugRuntime(Runtime):
    def __init__(self):
        print("Starting Debug Runtime...")
        Runtime.__init__(self, constants.DEBUG_FPS)
        self.stdout = sys.stdout
    
    def handle_custom_event(self, event):
        pass
    
    def handle_logic(self):
        # --- Getting frames and drawing  
        # New color frame: draw on screen
        if self.kinect.has_new_color_frame():
            frame = self.kinect.get_last_color_frame()
            self.draw_color_frame(frame, self.frame_surface)
            frame = None
        # get skeletondata if body frames exist
        if self.kinect.has_new_body_frame(): 
            self.skeletons = self.kinect.get_last_body_frame()
        # --- draw skeletons to _frame_surface
        if self.skeletons is not None: 
            body = self.skeletons.bodies[0]
            if(body.is_tracked): 
                joint_points = self.kinect.body_joints_to_color_space(body.joints)
                self.draw_body(body.joints, joint_points, constants.SKELETON_COLORS[0])                    
                features = self.extract_body_information(body)          
                self.stdout.write(features[0:3])
                #self.stdout.write(';'.join(str(x) for x in features) + "\n")
    
class RecordRuntime(Runtime):
    def __init__(self, action_number, person_number):
        print("Starting Record Runtime")
        Runtime.__init__(self, constants.DEFAULT_FPS)
        self.action_number = action_number
        self.person_number = person_number
        self.frame_count = 1 # index of frames
        self.directory = f'data\{constants.PERSONS[person_number]}\{constants.ACTIONS[action_number]}'
        if not os.path.exists(self.directory):
            os.makedirs(self.directory)
        self.stdout = open(f'{self.directory}\\joints.txt' , 'a')

        self.START_RECORDING_COUNTDOWN = pygame.USEREVENT + 1
        self.font = pygame.font.SysFont("Courier", 72)
        self.countdown_count = 5
        pygame.time.set_timer(self.START_RECORDING_COUNTDOWN, 1000)

    def exit(self):
        # convert all the images from bmp format to jpg format to reduce image size
        pass
    
    def handle_custom_event(self, event):
        if event.type == self.START_RECORDING_COUNTDOWN:
            #text = self.font.render(f"{self.countdown_count}", False, (255, 255, 255))
            #self.frame_surface.blit(text, (self.frame_surface.get_width() / 2, self.frame_surface.get_height()/2))
            print(self.countdown_count)
            if(self.countdown_count == 0):
                pygame.time.set_timer(self.START_RECORDING_COUNTDOWN, 0)
            else:    
                self.countdown_count -= 1

    def handle_logic(self):              
    
        if self.kinect.has_new_color_frame():
            frame = self.kinect.get_last_color_frame()
            self.draw_color_frame(frame, self.frame_surface)
            frame = None
            
        # get skeletondata if body frames exist
        if self.kinect.has_new_body_frame(): 
            self.skeletons = self.kinect.get_last_body_frame()
        if self.skeletons is not None: 
            for i in range(0, self.kinect.max_body_count):
                body = self.skeletons.bodies[i]
                if(body.is_tracked): 
                    if(self.countdown_count is 0):
                        
                        pygame.image.save(self.frame_surface, f'{self.directory}\\frame{self.frame_count}.bmp')
                        self.frame_count += 1

                        features = self.extract_body_information(body)
                        self.stdout.write(';'.join(str(x) for x in features) + f"\n")
                        # 
                    
                    joint_points = self.kinect.body_joints_to_color_space(body.joints)
                    self.draw_body(body.joints, joint_points, constants.SKELETON_COLORS[0])