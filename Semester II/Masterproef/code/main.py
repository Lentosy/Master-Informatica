#
# https://github.com/AravinthPanch/gesture-recognition-for-human-robot-interaction
import os
import sys 

# Redirect stdout to null so annoying package stdout doesn't get printed
old = sys.stdout
f = open(os.devnull, 'w')
sys.stdout = f

import argparse
import pygame
import ctypes

import constants  # constants can be found in constants.py
from runtime import * # import all runtime environments
# restore stdout
sys.stdout = old

def main(args=None):
    __main__ = "Kinect v2"

    parser = argparse.ArgumentParser()
    parser.add_argument("-r", "--record", dest="action_number", type=int, help="Makes the application record movements "
    +"and saves the information to disk. The resulting file is saved in data\[PERSON_NUMBER]_[ACTION_NAME]_[RECORD_COUNT] The argument of this option is an integer corresponding to the action"
    +"that is performed in the recording.\nPossible integers are:\n"
    + ' '.join(f"{i} {constants.ACTIONS[i]}" for i in range(0, len(constants.ACTIONS)))
    )
    parser.add_argument("-p", "--person", dest="person_number", type=int)
    parser.add_argument('-d', '--debug', action='store_true', help="Enables debug mode; a slower fps rate and only the head is tracked. All output is redirected to stdout.")
    args = parser.parse_args()
    
    if(args.action_number is not None and args.person_number is None):
        print("Using the -r option also requires the -p option")
        exit(-1)
    
    if(args.action_number is None and args.person_number is not None):
        print("Using the -o option also requires the -r option")
        exit(-1)

    if(args.action_number is not None and args.person_number is not None):
        runtime = RecordRuntime(args.action_number, args.person_number)
    elif(args.debug): 
        runtime = DebugRuntime()
    else:
        runtime = DefaultRuntime()
    runtime.run()

if __name__ == "__main__":
    main()
