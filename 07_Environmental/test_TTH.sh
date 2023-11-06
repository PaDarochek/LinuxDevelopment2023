echo 'TTH ./rhasher.c' | ./rhasher >test_TTH.log
if [[ $(grep '#define USE_READLINE' config.h) ]]; then sed -i '1d' test_TTH.log; fi
echo 'fd0dbc8654944a7444c48fab5d394658e5a6f8aca379518b' >test_TTH.ideal
cmp test_TTH.log test_TTH.ideal