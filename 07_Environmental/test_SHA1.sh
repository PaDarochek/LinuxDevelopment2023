echo 'SHA1 "abcde' | ./rhasher >test_SHA1.log
if [[ $(grep '#define USE_READLINE' config.h) ]]; then sed -i '1d' test_SHA1.log; fi
echo -n 'abcde' | sha1sum - >test_SHA1.ideal
sed 's/  -$//' -i test_SHA1.ideal
cmp test_SHA1.log test_SHA1.ideal