#! /bin/sh

echo "\nRunning autodefine.sh" | tee autodefine.log

# find absolute path
DIR=$( cd "$( dirname "$0" )" && pwd )

echo "kana-edit directory = $DIR\n"

INSTALLED=0

# installed font check
if [ -f /usr/share/fonts/truetype/msttcorefonts/arial.ttf ] ; then
	
	if ! grep -rl msttcorefonts/arial.ttf include/ >/dev/null ; then
		
		echo "WARNING: Detected 'arial.ttf' in standard font folder. Changing FONT_ARIAL to /usr/share/fonts/truetype/msttcorefonts/arial.ttf" | tee -a autodefine.log
	
		grep -rl resources/arial.ttf include/ | xargs sed -i 's~resources/arial.ttf~/usr/share/fonts/truetype/msttcorefonts/arial.ttf~' | tee -a autodefine.log

	fi

	INSTALLED=1

else
	
	echo "WARNING: No 'arial.ttf' detected in standard font folder. Keeping relative path for FONT_ARIAL. Consider installing 'msttcorefonts' or changing FONT_PATH to a valid truetype font." | tee -a autodefine.log

fi

# find absolute path
#DIR=$( cd "$( dirname "$0" )" && pwd )

#echo "\nkana-edit directory = $DIR\n"

if ! grep -rl /resources/mangal include/ >/dev/null ; then

	echo "WARNING: Replacing FONT_MANGAL with $DIR/resources/mangal.ttf. If you ran this script more than once, this path may be wrong. This can be fixed by changing it in include/defines.h" | tee -a autodefine.log
	grep -rl resources/mangal.ttf include/ | xargs sed -i 's~resources/mangal.ttf~'$DIR'/resources/mangal.ttf~' | tee -a autodefine.log

fi

if [ ! $INSTALLED = 1 ] ; then

	if ! grep -rl /resources/arial include/ >/dev/null ; then
	
		echo "WARNING: Replacing FONT_ARIAL with $DIR/resources/arial.ttf. If you ran this script more than once, this path may be wrong. This can be fixed by changing it in include/defines.h" | tee -a autodefine.log
	
		grep -rl resources/arial.ttf include/ | xargs sed -i 's~resources/arial.ttf~'$DIR'/resources/arial.ttf~' | tee -a autodefine.log
	
	fi

fi
