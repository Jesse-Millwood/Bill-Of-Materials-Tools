@echo off

set mcu=tiny25

set main=test

set ac=c:/avr/winavr

echo --std=gnu99 >opt.z
echo -lm >>opt.z
echo -fno-inline-small-functions >>opt.z
:echo -lprintf_min >>opt.z
:echo -fsigned-char >>opt.z
:echo -funsigned-bitfields >>opt.z
:echo -fpack-struct >>opt.z
:echo -fshort-enums >>opt.z

:echo -fno-tree-scev-cprop >>opt.z
:echo -fno-split-wide-types >>opt.z
:echo -fno-tree-loop-optimize >>opt.z
echo -fno-move-loop-invariants >>opt.z
echo -Wl,--relax >>opt.z
:echo --combine -fwhole-program >>opt.z

path %ac%\bin;%path%
avr-gcc.exe -dumpversion
avr-gcc.exe -xc *.c @opt.z -Os -mmcu=at%mcu% -Wall -gdwarf-2 -o %main%.out
::avr-gcc.exe -xc -E -dM -mmcu=at%mcu% main.c >macro.lst
if errorlevel 1 goto end

cmd /c avr-objdump.exe -h -S %main%.out >%main%.lst
cmd /c avr-objcopy.exe -O ihex %main%.out %main%.hex
avr-size.exe --format=avr --mcu=at%mcu% %main%.out
del %main%.out
del opt.z
:"C:\Programme\Atmel\AVR Tools\STK500\stk500.exe" -dAT%mcu% -e -pf -vf -iftest.hex
:call fboot -b38400 -ptest.hex -vtest.hex
:end
pause
