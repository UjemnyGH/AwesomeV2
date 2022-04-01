main:
	g++ -o linuxComp AwesomeV2/AwesomeV2.cpp AwesomeV2/stb_image_entrypoint.cpp -lGL -lGLEW -lglfw -lpthread

	./linuxComp

.SILENT: