
add:
	g++ -pthread -Wall -Werror -W -Wextra -std=c++11 -g addressbook.pb.cc write_data.cpp -o write_data -lprotobuf
	g++ -pthread -Wall -Werror -W -Wextra -std=c++11 -g addressbook.pb.cc read_data.cpp -o read_data -lprotobuf

proto:
	protoc -I=./ --cpp_out=./ ./addressbook.proto


clean:
	rm -rf addressbook.pb.* read_data write_data
