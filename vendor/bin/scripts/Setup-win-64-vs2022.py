import subprocess
import platform
import os
import re

current_dir = os.path.dirname(os.path.abspath(__file__))
solution_dir = os.path.join(current_dir, '../../../')

if platform.system() == 'Windows':
    try:
        vcxproj_glcore = os.path.join(solution_dir, 'Submodules/GLRenderer/GLRenderer.vcxproj')
        vcxproj_simulation = os.path.join(solution_dir, 'Simulation/Simulation.vcxproj')

        insert_count = 0
        glcore_guid = ''

        print('\nAttempting to retrieve "GLCore" GUID...')
        with open(vcxproj_glcore, "r") as f:
            lines = f.readlines()

            for i, line in enumerate(lines):    
                if "<ProjectGuid>" in line:
                    glcore_guid = line.strip().lstrip('<ProjectGuid>{').rstrip('}</ProjectGuid>').lower()
                    print('Success! -> ' + glcore_guid)
                    break
        
        f.close()

        print('\nAttempting to set reference to "GLCore" in "Simulation"...')
        print('Attempting to set pch source as glpch.cpp...')
        with open(vcxproj_simulation, "r") as f1:
            lines1 = f1.readlines()

            for j, line in enumerate(lines1):
                if '<Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />' in line:
                    lines1.insert(j, """
<ItemGroup>
    <ProjectReference Include="..\\Submodules\\GLRenderer\\GLRenderer.vcxproj">
      <Project>{""" + glcore_guid + """}</Project>
    </ProjectReference>
</ItemGroup>
""")
                    print('\nSuccess -> Added reference!')
                    break
                
        with open(vcxproj_simulation, "w") as f1:
            f1.writelines(lines1)

        with open(vcxproj_glcore, "r") as f2:
            lines2 = f2.readlines()
            for j, line in enumerate(lines2):
                if '<ClCompile Include="glpch.cpp" />' in line:
                    del lines2[j]
                    lines2.insert(j, '\t\t<ClCompile Include="glpch.cpp">\n' +
                                     "\t\t\t<PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">Create</PrecompiledHeader>\n" +
                                     "\t\t\t<PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='Distribution|x64'\">Create</PrecompiledHeader>\n" +
                                     "\t\t\t<PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">Create</PrecompiledHeader>\n" +
                                     "\t\t</ClCompile>\n")
                    print('Success! -> set pch source file!')
                    break
        with open(vcxproj_glcore, "r") as f2:
            for j, line in enumerate(lines2):
                if '<ClCompile Include="src\\utils\Timer.cpp" />' in line:
                    del lines2[j]
                    lines2.insert(j, '\t\t<ClCompile Include="src\\utils\Timer.cpp">\n' +
                                     "\t\t\t<PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">NotUsing</PrecompiledHeader>\n" +
                                     "\t\t\t<PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='Distribution|x64'\">NotUsing</PrecompiledHeader>\n" +
                                     "\t\t\t<PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">NotUsing</PrecompiledHeader>\n" +
                                     "\t\t</ClCompile>\n")
                    print('Success! -> configured pch settings in other source files!\n')
                    break

        with open(vcxproj_glcore, "w") as f2:
            f2.writelines(lines2)
            

        
    except subprocess.CalledProcessError as e:
        print("Script failed! --- ", e)

input('Press press ENTER to end setup...')
