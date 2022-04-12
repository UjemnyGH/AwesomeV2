main:
	g++ -o linuxComp AwesomeV2/test_code.cpp AwesomeV2/stb_image_entrypoint.cpp -lGL -lGLEW -lglfw -lpthread

	./linuxComp

.SILENT: