import argparse
import domain.constants as constants # constants can be found in constants.py
from runtime import * # import all runtime environments

def main(args=None):

    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(help = "Sub-command help")
    
    parser_record = subparsers.add_parser('record', 
                                          formatter_class = argparse.RawTextHelpFormatter, 
                                          help = "Makes the application record movements and saves the information to disk.") 
    
    parser_record.add_argument(dest = "person_number",
                               type = int, 
                               help = "One of the following integers:\n"
                                       + "\n".join(f"{i} {constants.PERSONS[i]}" for i in range(0, len(constants.PERSONS))))
   
    parser.add_argument('-d', '--debug', 
                        dest = 'debug', 
                        action = 'store_true', 
                        help = 'Enables debug mode. This has a slower FPS and writes out the feature vector for the head joint for every frame')

    parser.add_argument('-s', '--snapshot',
                        dest = 'snapshot',
                        type = int)
    
    args = parser.parse_args()
    
    # run one of the environments    
    try:
        if(args.debug):
            runtime = DebugRuntime()
        elif(args.snapshot):
            runtime = SnapshotRuntime(args.snapshot)
        elif( args.person_number is not None):
            runtime = RecordRuntime( args.person_number)
    except AttributeError as e:
        runtime = DefaultRuntime()
    
    runtime.run()

# only run the application when called as a script (from command line)
if __name__ == "__main__":
    main()