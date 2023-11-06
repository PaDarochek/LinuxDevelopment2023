echo 'md5 "abcde' | ./rhasher >test_md5.log
if [[ $(grep '#define USE_READLINE' config.h) ]]; then sed -i '1d' test_md5.log; fi
echo 'q1a02StAcTrMWviZhdS3hg==' >test_md5.ideal
cmp test_md5.log test_md5.ideal