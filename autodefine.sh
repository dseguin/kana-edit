#! /bin/sh

# find absolute path
DIR=$( cd "$( dirname "$0" )" && pwd )
cd $DIR

echo ""
echo " Running autodefine.sh" | tee autodefine.log

echo " kana-edit directory = $DIR" | tee -a autodefine.log
echo "" | tee -a autodefine.log

CHANGED=0

# change to absolute path
# FONT_MANGAL
if ! grep -rl /resources/mangal include/ >/dev/null ; then

	echo " WARNING: Replacing FONT_MANGAL with $DIR/resources/mangal.ttf." | tee -a autodefine.log
	
	grep -rl resources/mangal.ttf include/ 2>&1 | xargs sed -i "" -e 's~resources/mangal.ttf~'$DIR'/resources/mangal.ttf~' 2>&1 | tee -a autodefine.log

	CHANGED=1

fi

# FONT_ARIAL
if ! grep -rl /resources/arial include/ >/dev/null ; then
	
	echo " WARNING: Replacing FONT_ARIAL with $DIR/resources/arial.ttf." | tee -a autodefine.log

	grep -rl resources/arial.ttf include/ 2>&1 | xargs sed -i "" -e 's~resources/arial.ttf~'$DIR'/resources/arial.ttf~' 2>&1 | tee -a autodefine.log

	CHANGED=1
	
fi

# DEFAULT_SAVE_PATH
if grep -Frl ../kana include/ >/dev/null ; then
	
	echo " WARNING: Replacing DEFAULT_SAVE_PATH with $HOME/Documents." | tee -a autodefine.log

	grep -Frl ../kana include/ 2>&1 | xargs sed -i "" -e 's~\.\./kana~'$HOME'/Documents~' 2>&1 | tee -a autodefine.log

	CHANGED=1
	
fi

# MKDIR_PATH
MKDIR="/bin/mkdir"
MKDIRNEW=`command -v mkdir`
if [ ! $MKDIR = $MKDIRNEW ] ; then
	
	if ! grep -rl $MKDIRNEW include/ >/dev/null ; then

		echo " WARNING: Replacing MKDIR_PATH with $MKDIRNEW ." | tee -a autodefine.log

		grep -rl '/bin/mkdir' include/ 2>&1 | xargs sed -i "" -e 's~/bin/mkdir~'$MKDIRNEW'~' 2>&1 | tee -a autodefine.log

		CHANGED=1

	fi
	
fi

if [ $CHANGED = 1 ] ; then

	echo "" | tee -a autodefine.log
	echo " ! Some changes were made. See autodefine.log for details." | tee -a autodefine.log
	echo "" | tee -a autodefine.log

fi
