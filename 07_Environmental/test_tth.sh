echo 'tth ./rhasher.c' | ./rhasher >test_tth.log
if [[ $(grep '#define USE_READLINE' config.h) ]]; then sed -i '1d' test_tth.log; fi
echo '/Q28hlSUSnRExI+rXTlGWOWm+KyjeVGL' >test_tth.ideal
cmp test_tth.log test_tth.ideal