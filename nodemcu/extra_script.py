Import("env")
import datetime

curr_date = str(datetime.datetime.now().strftime("%d:%m:%y:%H:%M:%S"))
print("[BUILDING]", "SW_VERSION="+curr_date)

env.Append(CPPDEFINES = {'SW_VERSION': '\\"'+curr_date+'\\"'})

f = open(".pio/build/esp01_1m/firmware.json", "w")
f.write("{ \"sw\": \"%s\" }" % curr_date)
f.close()

# (Optional) Do not run extra script when IDE fetches C/C++ project metadata
from SCons.Script import COMMAND_LINE_TARGETS
if "idedata" in COMMAND_LINE_TARGETS:
    env.Exit(0)

#
# Upload actions
#

# env.Execute("node --version")
# def log(source, target, env):
#     print("before_upload AA")

# #
# # Custom actions when building program/firmware
# #
# env.AddPreAction("buildprog", log)
# env.AddPostAction("buildprog", log)
