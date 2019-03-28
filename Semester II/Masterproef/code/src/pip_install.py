import subprocess
import sys

packages = ['pykinect2', 'matplotlib', 'pygame', 'pandas']
for package in packages:
    subprocess.call([sys.executable, '-m' , 'pip', 'install', package])