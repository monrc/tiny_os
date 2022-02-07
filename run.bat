@echo off 
chcp 65001
CLS
title Bochs运行助手V1  
echo.
echo 输入1或2，选择bochs运行的模式
echo ==============================
echo.
echo 输入1，直接运行
echo.
echo 输入2，调试运行
echo.
echo ==============================
echo 运行失败删除当前文件夹下的 *.img.lock
echo.

cd /d "%~dp0"
set pats=%~dp0  

::首次使用,请修改下面的bochsPath的路径  
set bochsPath="D:\ProgramData\Bochs-2.7\bochs.exe" 
set bochsdbgPath="D:\ProgramData\Bochs-2.7\bochsdbg.exe" 
set bochs_config="-q -f bochsrc.bxrc"

goto :run

set /p user_input=请输入数字：
if %user_input% equ 1 goto :run
if %user_input% equ 2 goto :debug


:run  
echo run mode
echo.

%bochsPath% "%bochs_config%"

exit  


:debug  
echo debug mode
echo.

%bochsdbgPath% "%bochs_config%"

exit





