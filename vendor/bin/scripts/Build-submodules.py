import subprocess
import platform
import os
import re

current_dir = os.path.dirname(os.path.abspath(__file__))
solution_dir = os.path.join(current_dir, '../../../')

if platform.system() == 'Windows':
    try:
        glcore_lua = os.path.join(solution_dir, 'Submodules/GLRenderer/premake5.lua')
        print(f'GLCore lua path -> {glcore_lua}')

        insert_count = 0
        glcore_guid = ''

        print('\nAttempting to initialize submodule build scripts...')
        content = ''
        with open(glcore_lua, "r") as f:
            content = f.readlines()
        f.close()

        content_str = ''.join(content)
        new_content = re.sub('%{wks.location}/', '%{wks.location}/Submodules/', content_str, flags=re.IGNORECASE)

        with open(glcore_lua, "w") as f:
            f.write(new_content)
    except subprocess.CalledProcessError as e:
        print("Script failed! --- ", e)