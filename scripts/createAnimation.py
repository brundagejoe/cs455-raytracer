import os
import subprocess


def createValues(start_val, end_val, num_steps):
    # create a list of values between start_val and end_val split into num_steps steps
    return [start_val + (i / (num_steps - 1)) * (end_val - start_val)
            for i in range(num_steps)]


# get the current working directory
current_dir = os.getcwd()

# create the directory path for the "animation" folder
animation_dir = os.path.join(current_dir, "raytracer/animation")

# check if the directory already exists, and create it if it doesn't
if not os.path.exists(animation_dir):
    os.makedirs(animation_dir)
    print("Created directory:", animation_dir)
else:
    print("Directory", animation_dir, "already exists, removing files.")
    # remove all files in the directory:
    os.system("rm -rf " + animation_dir + "/*")


frame_rate = 24
total_seconds = 10
y_values = createValues(0, 10, 24 * total_seconds)
z_values = createValues(20, 1, 24 * total_seconds)

# for index, xVal in enumerate(values):
for i in range(frame_rate * total_seconds):
    command = f"./raytracer/raytracer -at[0,0,0] -from[0,{y_values[i]:2f},{z_values[i]:2f}] > raytracer/animation/image_{i+1:03d}.ppm"

    # use the subprocess module to run the command in a Bash shell
    subprocess.run(command, shell=True, check=True, cwd=".")

command = f"ffmpeg -i raytracer/animation/image_%03d.ppm -r {frame_rate} raytracer/animation/output.mp4"
subprocess.run(command, shell=True, check=True, cwd=".")

# remove all the ppm files from the directory

os.system("rm -rf " + animation_dir + "/*.ppm")
