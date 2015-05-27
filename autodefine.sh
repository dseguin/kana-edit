#! /bin/sh

echo "\n Running autodefine.sh" | tee autodefine.log

# find absolute path
DIR=$( cd "$( dirname "$0" )" && pwd )

echo " kana-edit directory = $DIR\n"

CHANGED=0
INSTALLED=0

# installed font check
if [ -f /usr/share/fonts/truetype/msttcorefonts/arial.ttf ] ; then
	
	if ! grep -rl msttcorefonts/arial.ttf include/ >/dev/null ; then
		
		echo " WARNING: Detected 'arial.ttf' in standard font folder. Changing FONT_ARIAL to /usr/share/fonts/truetype/msttcorefonts/arial.ttf" | tee -a autodefine.log
	
		grep -rl resources/arial.ttf include/ | xargs sed -i 's~resources/arial.ttf~/usr/share/fonts/truetype/msttcorefonts/arial.ttf~' | tee -a autodefine.log

		CHANGED=1

	fi

	INSTALLED=1

fi

# change to absolute path
if ! grep -rl /resources/mangal include/ >/dev/null ; then

	echo " WARNING: Replacing FONT_MANGAL with $DIR/resources/mangal.ttf. If you ran this script more than once, this path may be wrong. This can be fixed by changing it in include/defines.h" | tee -a autodefine.log
	
	grep -rl resources/mangal.ttf include/ | xargs sed -i 's~resources/mangal.ttf~'$DIR'/resources/mangal.ttf~' | tee -a autodefine.log

	CHANGED=1

fi

if [ $INSTALLED = 0 ] ; then

	if ! grep -rl /resources/arial include/ >/dev/null ; then
	
		echo " WARNING: Replacing FONT_ARIAL with $DIR/resources/arial.ttf. If you ran this script more than once, this path may be wrong. This can be fixed by changing it in include/defines.h" | tee -a autodefine.log
	
		grep -rl resources/arial.ttf include/ | xargs sed -i 's~resources/arial.ttf~'$DIR'/resources/arial.ttf~' | tee -a autodefine.log

		CHANGED=1
	
	fi

fi

if [ $CHANGED = 1 ] ; then

	echo "\n ! Some changes were made. See autodefine.log for details."

fi
