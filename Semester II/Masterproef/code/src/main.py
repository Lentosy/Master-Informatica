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
    subparsers = parser.add_subparsers(help = "Sub-command help")
    parser_record = subparsers.add_parser('record', formatter_class = argparse.RawTextHelpFormatter, help = "Makes the application record movements and saves the information to disk.") 
    
    parser_record.add_argument("action_number", type=int, help = "One of the following integers:\n"
    + "\n".join(f"{i} {constants.ACTIONS[i]}" for i in range(0, len(constants.ACTIONS)))
    )
    parser_record.add_argument("person_number", type=int, help = "One of the following integers:\n"
    + "\n".join(f"{i} {constants.PERSONS[i]}" for i in range(0, len(constants.PERSONS))))
   
    parser.add_argument('-d', '--debug', dest = 'debug', action = 'store_true', help = 'Enables debug mode')
    args = parser.parse_args()
    
    if(args.action_number is not None and args.person_number is None):
        print("Using the -a option also requires the -p option")
        exit(-1)
    
    if(args.action_number is None and args.person_number is not None):
        print("Using the -p option also requires the -a option")
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
