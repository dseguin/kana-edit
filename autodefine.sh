#! /bin/sh

# find absolute path
DIR=$( cd "$( dirname "$0" )" && pwd )
cd $DIR

# check uname
OS=$( uname )

echo ""
echo " Running autodefine.sh" | tee autodefine.log

echo " kana-edit directory = $DIR" | tee -a autodefine.log
echo "" | tee -a autodefine.log

CHANGED=0

# change to absolute path
# FONT_DEJAVU
if ! grep -rl /resources/dejavu include/ >/dev/null ; then

	echo " WARNING: Replacing FONT_DEJAVU with $DIR/resources/dejavu.ttf." | tee -a autodefine.log
	
	if [ "$OS" = FreeBSD ] ; then
		grep -rl resources/dejavu.ttf include/ 2>&1 | xargs sed -i "" -e 's~resources/dejavu.ttf~'$DIR'/resources/dejavu.ttf~' 2>&1 | tee -a autodefine.log
	else
		grep -rl resources/dejavu.ttf include/ 2>&1 | xargs sed -i 's~resources/dejavu.ttf~'$DIR'/resources/dejavu.ttf~' 2>&1 | tee -a autodefine.log
	fi

	CHANGED=1

fi

# FONT_UNIFONT
if ! grep -rl /resources/unifont include/ >/dev/null ; then
	
	echo " WARNING: Replacing FONT_UNIFONT with $DIR/resources/unifont.ttf." | tee -a autodefine.log

	if [ "$OS" = FreeBSD ] ; then
		grep -rl resources/unifont.ttf include/ 2>&1 | xargs sed -i "" -e 's~resources/unifont.ttf~'$DIR'/resources/unifont.ttf~' 2>&1 | tee -a autodefine.log
	else
		grep -rl resources/unifont.ttf include/ 2>&1 | xargs sed -i 's~resources/unifont.ttf~'$DIR'/resources/unifont.ttf~' 2>&1 | tee -a autodefine.log
	fi

	CHANGED=1
	
fi

# DEFAULT_SAVE_PATH
if grep -Frl "../kana" include/ >/dev/null ; then
	
	echo " WARNING: Replacing DEFAULT_SAVE_PATH with $HOME/Documents." | tee -a autodefine.log

	if [ "$OS" = FreeBSD ] ; then
		grep -Frl "../kana" include/ 2>&1 | xargs sed -i "" -e 's~\.\./kana~'$HOME'/Documents~' 2>&1 | tee -a autodefine.log
	else
		grep -Frl "../kana" include/ 2>&1 | xargs sed -i 's~\.\./kana~'$HOME'/Documents~' 2>&1 | tee -a autodefine.log
	fi

	CHANGED=1
	
fi

# MKDIR_PATH
MKDIR="/bin/mkdir"
MKDIRNEW=`command -v mkdir`
if [ ! $MKDIR = $MKDIRNEW ] ; then
	
	if ! grep -rl $MKDIRNEW include/ >/dev/null ; then

		echo " WARNING: Replacing MKDIR_PATH with $MKDIRNEW ." | tee -a autodefine.log

		if [ "$OS" = FreeBSD ] ; then
			grep -rl '/bin/mkdir' include/ 2>&1 | xargs sed -i "" -e 's~/bin/mkdir~'$MKDIRNEW'~' 2>&1 | tee -a autodefine.log
		else
			grep -rl '/bin/mkdir' include/ 2>&1 | xargs sed -i 's~/bin/mkdir~'$MKDIRNEW'~' 2>&1 | tee -a autodefine.log
		fi

		CHANGED=1

	fi
	
fi

if [ $CHANGED = 1 ] ; then

	echo "" | tee -a autodefine.log
	echo " ! Some changes were made. See 'autodefine.log' and 'include/defines.h'." | tee -a autodefine.log
	echo "" | tee -a autodefine.log

fi

echo ""
echo "  Done making changes to 'defines.h'."
echo "      [d + enter] - View changes to 'defines.h'"
echo "      [a + enter] - Run autogen.sh"
echo "      [enter] - Quit"
OUTCOME=0
while true; do
	read io
	case $io in
		[Dd] ) OUTCOME=1 && break;;
		[Aa] ) OUTCOME=2 && break;;
		"" ) exit;;
		* ) ;;
	esac
done

if [ $OUTCOME = 1 ] ; then
	exec pager include/defines.h
	exit 0
fi

if [ $OUTCOME = 2 ] ; then
	exec ./autogen.sh
	exit 0
fi

echo ""
echo "  Something went wrong. Exiting."
echo ""
exit 1
