from pykinect2 import PyKinectV2
from pykinect2.PyKinectV2 import *
from pykinect2 import PyKinectRuntime

import sys
import constants
import ctypes
import pygame

class Runtime():
    def __init__(self):
        pygame.init()     
        # Used to manage how fast the screen updates
        self.clock = pygame.time.Clock()
        # Set the width and height of the screen [width, height]
        self.infoObject = pygame.display.Info()
        self.screen = pygame.display.set_mode((self.infoObject.current_w >> 1, self.infoObject.current_h >> 1), 
                                               pygame.HWSURFACE|pygame.DOUBLEBUF|pygame.RESIZABLE, 32)
        pygame.display.set_caption("KinectV2 for Windows")
        # Loop until the user clicks the close button.
        self.done = False
        # Used to manage how fast the screen updates
        self.clock = pygame.time.Clock()
        # Kinect runtime object, we want only color and depth frames 
        self.kinect = PyKinectRuntime.PyKinectRuntime(PyKinectV2.FrameSourceTypes_Color | PyKinectV2.FrameSourceTypes_Depth | PyKinectV2.FrameSourceTypes_Body)
        # back buffer surface for getting Kinect color frames, 32bit color, width and height equal to the Kinect color frame size
        self.frame_surface = pygame.Surface((self.kinect.color_frame_desc.Width, self.kinect.color_frame_desc.Height), 0, 32)
        # skeleton data
        self.bodies = None

        
    def extract_frame_information(self, body):
        joints = body.joints  
        orientations = body.joint_orientations
        
        depth_points = self.kinect.body_joints_to_depth_space(joints)
        depth_list = self.kinect.get_last_depth_frame()
        
        coordinates = []
        quaternions = []
        
        if __debug__:
            length = 1
        else:
            length = len(constants.JOINTS)
        
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
    
    # This function draws a straight line segment starting from joint0 to joint1
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


class DefaultRuntime(Runtime):
    def __init__(self):
        Runtime.__init__(self)
    def run(self):
        # -------- Main Program Loop -----------
        while not self.done:
            # --- Main event loop
            for event in pygame.event.get(): # User did something
                if event.type == pygame.QUIT: # If user clicked close
                    self.done = True # Flag that we are done so we exit this loop
                elif event.type == pygame.VIDEORESIZE: # window resized
                    self.screen = pygame.display.set_mode(event.dict['size'], 
                                               pygame.HWSURFACE|pygame.DOUBLEBUF|pygame.RESIZABLE, 32)
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
                    
            
            # --- copy back buffer surface pixels to the screen, resize it if needed and keep aspect ratio
            # --- (screen size may be different from Kinect's color frame size) 
            h_to_w = float(self.frame_surface.get_height()) / self.frame_surface.get_width()
            target_height = int(h_to_w * self.screen.get_width())
            surface_to_draw = pygame.transform.scale(self.frame_surface, (self.screen.get_width(), target_height));
            self.screen.blit(surface_to_draw, (0,0))
            surface_to_draw = None
            pygame.display.update()

            # Neccesary for pygame after drawing lines and circles etc
            pygame.display.flip()            
            self.clock.tick(constants.DEFAULT_FPS)
        # Close the Kinect sensor, close the window and quit.
        self.kinect.close()
        pygame.quit()


class DebugRuntime(Runtime):
    def __init__(self):
        Runtime.__init__(self)
        self.stdout = sys.stdout
    
    def run(self):
        # -------- Main Program Loop -----------
        while not self.done:
            # --- Main event loop
            for event in pygame.event.get(): # User did something
                if event.type == pygame.QUIT: # If user clicked close
                    self.done = True # Flag that we are done so we exit this loop
                elif event.type == pygame.VIDEORESIZE: # window resized
                    self.screen = pygame.display.set_mode(event.dict['size'], 
                                               pygame.HWSURFACE|pygame.DOUBLEBUF|pygame.RESIZABLE, 32)
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
                    features = self.extract_frame_information(body)          
                    self.stdout.write(';'.join(str(x) for x in features) + "\n")
    
            
            # --- copy back buffer surface pixels to the screen, resize it if needed and keep aspect ratio
            # --- (screen size may be different from Kinect's color frame size) 
            h_to_w = float(self.frame_surface.get_height()) / self.frame_surface.get_width()
            target_height = int(h_to_w * self.screen.get_width())
            surface_to_draw = pygame.transform.scale(self.frame_surface, (self.screen.get_width(), target_height));
            self.screen.blit(surface_to_draw, (0,0))
            surface_to_draw = None
            pygame.display.update()

            # Neccesary for pygame after drawing lines and circles etc
            pygame.display.flip()
            self.clock.tick(constants.DEBUG_FPS)
        # Close the Kinect sensor, close the window and quit.
        self.kinect.close()
        pygame.quit()


class RecordRuntime(Runtime):
    def __init__(self, action_number, person_number):
        Runtime.__init__(self)
        self.action_number = action_number
        self.person_number = person_number
        self.record_count = 1
        self.stdout = open(f"data\{constants.PERSONS[self.person_number]}_{constants.ACTIONS[self.action_number]}_{self.record_count}.txt", 'a')

    def run(self):
        print(f"Starting recording for action {constants.ACTIONS[self.action_number]}\nActor: {constants.PERSONS[self.person_number]}")
        pygame.time.set_timer(31, 7000)
        # -------- Main Program Loop -----------
        while not self.done:
            # --- Main event loop
            for event in pygame.event.get(): # User did something
                if event.type == pygame.QUIT: # If user clicked close
                    self.done = True # Flag that we are done so we exit this loop
                elif event.type == 31:
                    pygame.time.delay(2000)
                    self.record_count += 1
                    self.stdout = open(f"data\{constants.PERSONS[self.person_number]}_{constants.ACTIONS[self.action_number]}_{self.record_count}.txt", 'a')

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
                    features = self.extract_frame_information(body)          
                    self.stdout.write(';'.join(str(x) for x in features) + f";{self.action_number}\n")
            
            # --- copy back buffer surface pixels to the screen, resize it if needed and keep aspect ratio
            # --- (screen size may be different from Kinect's color frame size) 
            h_to_w = float(self.frame_surface.get_height()) / self.frame_surface.get_width()
            target_height = int(h_to_w * self.screen.get_width())
            surface_to_draw = pygame.transform.scale(self.frame_surface, (self.screen.get_width(), target_height));
            self.screen.blit(surface_to_draw, (0,0))
            surface_to_draw = None
            pygame.display.update()
            self.clock.tick(constants.DEFAULT_FPS)
        # Close the Kinect sensor, close the window and quit.
        self.kinect.close()
        pygame.quit()
