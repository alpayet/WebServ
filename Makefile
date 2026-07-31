.PHONY : all d vlg clean fclean re

#files
SRC_FILES = main.cpp \
	server/Server.cpp \
	server/fd/Fd.cpp \
	server/handler/TcpListenerHandler.cpp server/handler/ConnectionHandler.cpp \
	server/handler/TcpConnectionFactory.cpp \
	server/protocol/TestProtocol.cpp \
	server/protocol/HttpProtocolFactory.cpp server/protocol/HttpProtocol.cpp \
	server/reactor/Reactor.cpp \
	server/reactor/demultiplexer/EpollDemultiplexer.cpp \
	server/reactor/demultiplexer/KqueueDemultiplexer.cpp \
	server/transport/socket.cpp server/transport/TcpTransport.cpp \
	server/transport/endpoint/TcpEndpoint.cpp server/transport/endpoint/Endpoints.cpp \
	server/transport/endpoint/EndpointException.cpp \
	server/transport/endpoint/build_endpoints.cpp \
	server/utils/utils.cpp \
	infrastructure/constants.cpp \
	infrastructure/storage/file_system/TempWriter.cpp \
	infrastructure/storage/file_system/Storage.cpp \
	infrastructure/storage/file_system/Reader.cpp \
	infrastructure/storage/file_system/fileSystem.cpp \
	infrastructure/storage/file_system/Exception.cpp \
	infrastructure/storage/file_system/DirectoryExplorer.cpp \
	infrastructure/storage/file_system/constants.cpp \
	infrastructure/parsing/utils.cpp \
	infrastructure/parsing/line_reader.cpp \
	infrastructure/parsing/header_parser.cpp \
	infrastructure/parsing/constants.cpp \
	infrastructure/http/methods.cpp \
	infrastructure/http/Handler.cpp \
	infrastructure/http/Context.cpp \
	infrastructure/http/router/Router.cpp \
	infrastructure/http/response/Sender.cpp \
	infrastructure/http/response/ResponseBuilder.cpp \
	infrastructure/http/response/Response.cpp \
	infrastructure/http/response/HeaderBlockSerializer.cpp \
	infrastructure/http/response/get_status_reason.cpp \
	infrastructure/http/response/get_default_body.cpp \
	infrastructure/http/request/Request.cpp \
	infrastructure/http/request/Parser.cpp \
	infrastructure/http/presenters/success_lookup.cpp \
	infrastructure/http/presenters/ServeStaticResourcePresenter.cpp \
	infrastructure/http/presenters/get_listing_html.cpp \
	infrastructure/http/presenters/DeleteStaticResourcePresenter.cpp \
	infrastructure/http/mappers/ServeStaticResourceDtoMapper.cpp \
	infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.cpp \
	infrastructure/http/mappers/DeleteStaticResourceDtoMapper.cpp \
	infrastructure/http/mappers/CgiResponseMapper.cpp \
	infrastructure/http/exceptions/ReturnException.cpp \
	infrastructure/http/exceptions/Exception.cpp \
	infrastructure/http/exceptions/error_lookup.cpp \
	infrastructure/http/controllers/ServeStaticResourceController.cpp \
	infrastructure/http/controllers/ExecuteDynamicResourceController.cpp \
	infrastructure/http/controllers/DeleteStaticResourceController.cpp \
	cgi/Response.cpp \
	cgi/Parser.cpp \
	cgi/Exception.cpp \
	cgi/constants.cpp \
	application/Exception.cpp \
	application/use_cases/serve_static_resource/ServeStaticResource.cpp \
	application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.cpp \
	application/use_cases/delete_static_resource/DeleteStaticResource.cpp \
	domain/Exception.cpp \
	domain/value_objects/ResourceMetaData.cpp \
	domain/entities/StaticResource.cpp \
	domain/entities/DynamicResource.cpp \
	infrastructure/config/Tokenizer.cpp \
	infrastructure/config/Semantic.cpp \
	infrastructure/config/Parser.cpp \
	infrastructure/config/ServerConfig.cpp \
	infrastructure/config/Config.cpp

# directories
SRC_DIR = src/
OBJ_DIR = obj/

# files full paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
DEP = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.d))

NAME = webserv

CC = c++
CFLAGS = -Wall -Wextra -Weffc++ -MMD -MP -std=c++98 -g
CFLAGS += $(EXTRA_FLAGS)
IFLAGS = -I $(SRC_DIR)
MAKE = @make --no-print-directory -j

DEBUG_VALGRIND = valgrind --leak-check=full --show-leak-kinds=all -s

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

-include $(DEP)

d :
	$(MAKE) re EXTRA_FLAGS='$(EXTRA_FLAGS) -DWS_DEBUG'

vlg : all
	$(DEBUG_VALGRIND) ./$(NAME) $(ARGS)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean
	$(MAKE) all
