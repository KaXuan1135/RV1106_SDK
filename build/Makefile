all: demo

date=`date +%m%d`
pack_dir=../rv1106_sdk_custom

demo: 
# 	cd ../app  && make
	cd ../app && make clean && make
	cd ../ai && make clean && make
	cd ../demo  && make clean && make
app: codec ai_process mcu  atLib webrtc
	cd ../socket_server && make
	cd ../encNet  && make
	cd ../param  && make
	cd ../misc  && make
	cd ../logLib &&  make
	cd ../network && make
	cd ../stream   && make
	cd ../ptzLib  && make
	cd ../gb28181 && make
	cd ../hdLib && make
	cd ../voip && make
	cd ../wifi && make
	cd ../socket_server && make
	cd ../commLib && make
webrtc:
	 cd ../webrtc && make
codec:
	cd ../codec && make
	
ai:
	cd ../ai && make

ai_process:
	cd ../ai_process && make	
mcu:
	cd ../mcu && make
setting:
	cd ../setting && make
	
atLib:
	cd ../atLib && make	
platform:
	cd ../cnc &&make
clean: 
	cd ../demo && make clean
	rm -rf rv1106_ipc
	cd ../app && make clean
distclean:
	cd ../demo && make clean
	cd ../codec && make clean
	cd ../app && make clean
	cd ../misc && make clean
	cd ../logLib && make clean
	cd ../network && make clean
	cd ../stream && make clean
	cd ../ai && make clean
	cd ../mcu && make clean
	cd ../setting && make clean
	cd ../mcu && make clean
	cd ../param && make clean
	cd ../ptzLib && make clean
	cd ../encNet && make clean
	cd ../atLib && make clean 
	cd ../hdLib && make clean
	cd ../voip && make clean
	cd ../wifi && make clean
	cd ../socket_server && make clean
	cd ../webrtc && make clean
	cd ../ai_process && make clean
	rm -rf rv1106_ipc


custom:app ai atLib demo
	rm -rf $(pack_dir)
	@[ -e $(pack_dir) ] || mkdir -p $(pack_dir)
	@[ -e $(pack_dir)/build ] || mkdir -p $(pack_dir)/build
	cp -rf ../env.sh ../app ../ai  ../include ../demo  ../lib $(pack_dir)
#	cp -rf ../env.sh ../app ../ai  ../include ../demo  ../webrtc ../lib $(pack_dir)
	cp -rf ../build/Makefile  ../build/Makefile.param ../build/rv1106_ipc $(pack_dir)/build
pack:
	cd ../ &&  tar zcf rv1106_sdk_custom_${date}.tar.gz rv1106_sdk_custom
install:
	\cp -rf rv1106_ipc /home/nosword/nfs/rv1106
	\cp -rf rv1106_ipc /mnt/hgfs/work/tftp
