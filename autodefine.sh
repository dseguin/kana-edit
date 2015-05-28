#! /bin/sh

echo ""
echo " Running autodefine.sh" | tee autodefine.log

# find absolute path
DIR=$( cd "$( dirname "$0" )" && pwd )

echo " kana-edit directory = $DIR" | tee -a autodefine.log
echo "" | tee -a autodefine.log

CHANGED=0

# change to absolute path
# FONT_MANGAL
if ! grep -rl /resources/mangal include/ >/dev/null ; then

	echo " WARNING: Replacing FONT_MANGAL with $DIR/resources/mangal.ttf." | tee -a autodefine.log
	
	grep -rl resources/mangal.ttf include/ | xargs sed -i 's~resources/mangal.ttf~'$DIR'/resources/mangal.ttf~' | tee -a autodefine.log

	CHANGED=1

fi

# FONT_ARIAL
if ! grep -rl /resources/arial include/ >/dev/null ; then
	
	echo " WARNING: Replacing FONT_ARIAL with $DIR/resources/arial.ttf." | tee -a autodefine.log

	grep -rl resources/arial.ttf include/ | xargs sed -i 's~resources/arial.ttf~'$DIR'/resources/arial.ttf~' | tee -a autodefine.log

	CHANGED=1
	
fi

# DEFAULT_SAVE_PATH
if grep -rl '$HOME'/Documents include/ >/dev/null ; then
	
	echo " WARNING: Replacing DEFAULT_SAVE_PATH with $HOME/Documents." | tee -a autodefine.log

	grep -rl '$HOME'/Documents include/ | xargs sed -i 's~$HOME/Documents~'$HOME'/Documents~' | tee -a autodefine.log

	CHANGED=1
	
fi

# MKDIR_PATH
MKDIR="/bin/mkdir"
MKDIRNEW=`command -v mkdir`
if [ ! $MKDIR = $MKDIRNEW ] ; then
	
	if grep -rl $MKDIR include/ >/dev/null ; then

		echo " WARNING: Replacing MKDIR_PATH with $MKDIRNEW ." | tee -a autodefine.log

		grep -rl '/bin/mkdir' include/ | xargs sed -i 's~/bin/mkdir~'$MKDIRNEW'~' | tee -a autodefine.log

		CHANGED=1

	fi
	
fi

if [ $CHANGED = 1 ] ; then

	echo "" | tee -a autodefine.log
	echo " ! Some changes were made. See autodefine.log for details." | tee -a autodefine.log
	echo "" | tee -a autodefine.log

fi
