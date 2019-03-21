from pykinect2 import PyKinectV2
from pykinect2.PyKinectV2 import *
from pykinect2 import PyKinectRuntime

import sys
import constants
import ctypes
import pygame

START_RECORDING = 30
NEXT_TAKE = 31

class Runtime():
    def __init__(self, fps):
        pygame.init()     
        # Set the width and height of the screen [width, height]
        self.infoObject = pygame.display.Info()
        self.screen = pygame.display.set_mode((self.infoObject.current_w >> 1, self.infoObject.current_h >> 1), 
                                               pygame.HWSURFACE|pygame.DOUBLEBUF|pygame.RESIZABLE, 32)
        pygame.display.set_caption("KinectV2 for Windows")
        # Loop until the user clicks the close button.
        self.done = False
        # Used to manage how fast the screen updates
        self.clock = pygame.time.Clock()
        # Kinect runtime object, we only want color and depth frames 
        self.kinect = PyKinectRuntime.PyKinectRuntime(PyKinectV2.FrameSourceTypes_Color | PyKinectV2.FrameSourceTypes_Depth | PyKinectV2.FrameSourceTypes_Body)
        # back buffer surface for getting Kinect color frames, 32bit color, width and height equal to the Kinect color frame size
        self.frame_surface = pygame.Surface((self.kinect.color_frame_desc.Width, self.kinect.color_frame_desc.Height), 0, 32)
        # skeleton data
        self.bodies = None
        # frames per second to run at
        self.fps = fps
   
    def extract_body_information(self, body):
        joints = body.joints  
        orientations = body.joint_orientations
        
        depth_points = self.kinect.body_joints_to_depth_space(joints)
        depth_list = self.kinect.get_last_depth_frame()
        
        coordinates = []
        quaternions = []
        
        for j in range(0, length):
            try:
                x = depth_points[j].x                    
                y = depth_points[j].y
                c = int(y) * 512 + int(x) # depth index to be used in _depth
                if(c > len(depth_list) or (x < 0 and y < 0)):
                    z = -1 # joint is not in view, so no depth data exists
                else:
                    z = depth_list[c]
                coordinates.extend([x, y, z])
                
                quaternions.extend([orientations[j].Orientation.x, orientations[j].Orientation.y, orientations[j].Orientation.z, orientations[j].Orientation.w])
            except: # error ocurred, treat joint as invalid
                x = -1
                y = -1
                z = -1 
        return [';'.join(str(c) for c in coordinates), ';'.join(str(q) for q in quaternions)]
    def is_joint_tracked(self, joint):
        jointState = joint.TrackingState
        return not jointState == PyKinectV2.TrackingState_NotTracked and not jointState == PyKinectV2.TrackingState_Inferred
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
        for i in range(len(constants.CONNECTIONS)):
            self.draw_body_bone(joints, jointPoints, color, constants.CONNECTIONS[i][0], constants.CONNECTIONS[i][1])
            # optimalisation: CONNECTIONS list (from constants.py) contains  an equal amount of elements as the JOINTS list. So it can be put in one loop
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
            self.run_logic()
            self.copy_back_buffer()
            self.clock.tick(self.fps)
        self.exit()

    def handle_event(self, event):
        TypeError("test")
        # throw NotImplementedException
    def run_logic(self):
        TypeError("test")
    # throw NotImplementedException
class DefaultRuntime(Runtime):
    def __init__(self):
        print("Starting Default Runtime...")
        Runtime.__init__(self, constants.DEFAULT_FPS)
    def handle_event(self, event):    
        if event.type == pygame.QUIT: # If user clicked close
            self.done = True # Flag that we are done so we exit this loop
        elif event.type == pygame.VIDEORESIZE: # window resized
            self.screen = pygame.display.set_mode(event.dict['size'], 
                                       pygame.HWSURFACE|pygame.DOUBLEBUF|pygame.RESIZABLE, 32)
    def run_logic(self):
        if self.kinect.has_new_color_frame():
                frame = self.kinect.get_last_color_frame()
                self.draw_color_frame(frame, self.frame_surface)
                frame = None
        # get skeletondata if body frames exist
        if self.kinect.has_new_body_frame(): 
            self.bodies = self.kinect.get_last_body_frame()
        # --- draw skeletons to _frame_surface
        if self.bodies is not None: 
            for i in range(0, self.kinect.max_body_count):
                body = self.bodies.bodies[i]
                if not body.is_tracked: 
                    continue 
                joint_points = self.kinect.body_joints_to_color_space(body.joints)
            

class DebugRuntime(Runtime):
    def __init__(self):
        print("Starting Debug Runtime...")
        Runtime.__init__(self, constants.DEBUG_FPS)
        self.stdout = sys.stdout
    
    def handle_event(self, event):
        if event.type == pygame.QUIT: # If user clicked close
                self.done = True # Flag that we are done so we exit this loop
        elif event.type == pygame.VIDEORESIZE: # window resized
            self.screen = pygame.display.set_mode(event.dict['size'], 
                                       pygame.HWSURFACE|pygame.DOUBLEBUF|pygame.RESIZABLE, 32)
    
    def run_logic(self):
        # --- Getting frames and drawing  
        # New color frame: draw on screen
        if self.kinect.has_new_color_frame():
            frame = self.kinect.get_last_color_frame()
            self.draw_color_frame(frame, self.frame_surface)
            frame = None
        # get skeletondata if body frames exist
        if self.kinect.has_new_body_frame(): 
            self.bodies = self.kinect.get_last_body_frame()
        # --- draw skeletons to _frame_surface
        if self.bodies is not None: 
            for i in range(0, self.kinect.max_body_count):
                body = self.bodies.bodies[i]
                if not body.is_tracked: 
                    continue 
                joint_points = self.kinect.body_joints_to_color_space(body.joints)
                self.draw_body(body.joints, joint_points, constants.SKELETON_COLORS[0])                    
                features = self.extract_body_information(body)          
                self.stdout.write(';'.join(str(x) for x in features) + "\n")
    

class RecordRuntime(Runtime):
    def __init__(self, action_number, person_number):
        print("Starting Record Runtime")
        Runtime.__init__(self, constants.DEFAULT_FPS)
        self.action_number = action_number
        self.person_number = person_number
        self.record_count = 1
        self.stdout = open(f"data\{constants.PERSONS[self.person_number]}_{constants.ACTIONS[self.action_number]}_{self.record_count}.txt", 'a')
        self.skip = True # wether or not to skip the feature extraction process: this is used at the beginning of the recording, to allow the person to get ready
    def handle_event(self, event):
        if event.type == START_RECORDING:
            print("Start recording")
            print(f"Take {self.record_count}")                    
            pygame.time.set_timer(START_RECORDING, 0)
            pygame.time.set_timer(NEXT_TAKE, 5000)
            self.skip = False
        elif event.type == NEXT_TAKE:
            pygame.time.delay(2000)
            if(self.record_count == 10):
                self.done = True
                break
            self.record_count += 1
            print(f"Take {self.record_count}")
            self.stdout = open(f"data\{constants.PERSONS[self.person_number]}_{constants.ACTIONS[self.action_number]}_{self.record_count}.txt", 'a')
        elif event.type == pygame.QUIT: # If user clicked close
            self.done = True # Flag that we are done so we exit this loop
    

    def run_logic(self):
        pygame.time.set_timer(START_RECORDING, 5000)          
        if self.kinect.has_new_color_frame():
            frame = self.kinect.get_last_color_frame()
            self.draw_color_frame(frame, self.frame_surface)
            frame = None
        # get skeletondata if body frames exist
        if self.kinect.has_new_body_frame(): 
            self.bodies = self.kinect.get_last_body_frame()
        if self.bodies is not None: 
            for i in range(0, self.kinect.max_body_count):
                body = self.bodies.bodies[i]
                if not body.is_tracked: 
                    continue 
                
                joint_points = self.kinect.body_joints_to_color_space(body.joints)
                self.draw_body(body.joints, joint_points, constants.SKELETON_COLORS[0])
                if(skip):
                    break
                features = self.extract_body_information(body)          
                self.stdout.write(';'.join(str(x) for x in features) + f";{self.action_number}\n")
            
            
#    def run(self):
#        print(f"Starting recording for action {constants.ACTIONS[self.action_number]}\nActor: {constants.PERSONS[self.person_number]}")  
#        skip = True
#        pygame.time.set_timer(START_RECORDING, 5000)      
#        # -------- Main Program Loop -----------
#        while not self.done:
#            # --- Main event loop
#            for event in pygame.event.get():
#                if event.type == START_RECORDING:
#                    print("Start recording")
#                    print(f"Take {self.record_count}")                    
#                    pygame.time.set_timer(START_RECORDING, 0)
#                    pygame.time.set_timer(NEXT_TAKE, 5000)
#                    skip = False
#                elif event.type == NEXT_TAKE:
#                    pygame.time.delay(2000)
#                    if(self.record_count == 10):
#                        self.done = True
#                        break
#                    self.record_count += 1
#                    print(f"Take {self.record_count}")
#                    self.stdout = open(f"data\{constants.PERSONS[self.person_number]}_{constants.ACTIONS[self.action_number]}_{self.record_count}.txt", 'a')
#                elif event.type == pygame.QUIT: # If user clicked close
#                    self.done = True # Flag that we are done so we exit this loop
#            
#            if self.kinect.has_new_color_frame():
#                frame = self.kinect.get_last_color_frame()
#                self.draw_color_frame(frame, self.frame_surface)
#                frame = None
#            # get skeletondata if body frames exist
#            if self.kinect.has_new_body_frame(): 
#                self.bodies = self.kinect.get_last_body_frame()
#
#            if self.bodies is not None: 
#                for i in range(0, self.kinect.max_body_count):
#                    body = self.bodies.bodies[i]
#                    if not body.is_tracked: 
#                        continue 
#                    
#                    joint_points = self.kinect.body_joints_to_color_space(body.joints)
#                    self.draw_body(body.joints, joint_points, constants.SKELETON_COLORS[0])
#                    if(skip):
#                        break
#                    features = self.extract_body_information(body)          
#                    self.stdout.write(';'.join(str(x) for x in features) + f";{self.action_number}\n")
#            
#            copy_back_buffer()
#            pygame.display.flip()
#            self.clock.tick(self.fps)
#        self.exit()