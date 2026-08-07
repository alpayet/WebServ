.PHONY : all d vlg clean fclean re

#files
SRC_FILES = \
	main.cpp \
	infrastructure/config/Tokenizer.cpp \
	infrastructure/config/ServerConfig.cpp \
	infrastructure/config/Semantic.cpp \
	infrastructure/config/Config.cpp \
	infrastructure/config/Parser.cpp \
	infrastructure/parsing/line_reader.cpp \
	infrastructure/parsing/constants.cpp \
	infrastructure/parsing/utils.cpp \
	infrastructure/parsing/header_parser.cpp \
	infrastructure/storage/file_system/constants.cpp \
	infrastructure/storage/file_system/Storage.cpp \
	infrastructure/storage/file_system/fileSystem.cpp \
	infrastructure/storage/file_system/DirectoryExplorer.cpp \
	infrastructure/storage/file_system/Reader.cpp \
	infrastructure/storage/file_system/TempWriter.cpp \
	infrastructure/storage/file_system/Exception.cpp \
	infrastructure/storage/file_system/fd/Fd.cpp \
	infrastructure/server/utils/Logger.cpp \
	infrastructure/server/utils/utils.cpp \
	infrastructure/server/handler/TcpConnectionFactory.cpp \
	infrastructure/server/handler/ConnectionHandler.cpp \
	infrastructure/server/handler/TcpListenerHandler.cpp \
	infrastructure/server/Server.cpp \
	infrastructure/server/transport_protocol/endpoint/build_endpoints.cpp \
	infrastructure/server/transport_protocol/endpoint/Endpoints.cpp \
	infrastructure/server/transport_protocol/endpoint/TcpEndpoint.cpp \
	infrastructure/server/transport_protocol/endpoint/EndpointException.cpp \
	infrastructure/server/transport_protocol/socket.cpp \
	infrastructure/server/transport_protocol/TcpTransport.cpp \
	infrastructure/server/reactor/demultiplexer/EpollDemultiplexer.cpp \
	infrastructure/server/reactor/demultiplexer/KqueueDemultiplexer.cpp \
	infrastructure/server/reactor/Reactor.cpp \
	infrastructure/server/application_protocol/http/ProtocolFactory.cpp \
	infrastructure/server/application_protocol/http/controllers/DeleteStaticResourceController.cpp \
	infrastructure/server/application_protocol/http/controllers/ServeStaticResourceController.cpp \
	infrastructure/server/application_protocol/http/controllers/ExecuteDynamicResourceController.cpp \
	infrastructure/server/application_protocol/http/request/Parser.cpp \
	infrastructure/server/application_protocol/http/request/Request.cpp \
	infrastructure/server/application_protocol/http/update_keep_alive_status.cpp \
	infrastructure/server/application_protocol/http/response/get_default_body.cpp \
	infrastructure/server/application_protocol/http/response/ResponseBuilder.cpp \
	infrastructure/server/application_protocol/http/response/HeaderBlockSerializer.cpp \
	infrastructure/server/application_protocol/http/response/get_status_reason.cpp \
	infrastructure/server/application_protocol/http/response/Sender.cpp \
	infrastructure/server/application_protocol/http/response/Response.cpp \
	infrastructure/server/application_protocol/http/router/Router.cpp \
	infrastructure/server/application_protocol/http/mappers/ExecuteDynamicResourceDtoMapper.cpp \
	infrastructure/server/application_protocol/http/mappers/CgiResponseMapper.cpp \
	infrastructure/server/application_protocol/http/mappers/ServeStaticResourceDtoMapper.cpp \
	infrastructure/server/application_protocol/http/mappers/DeleteStaticResourceDtoMapper.cpp \
	infrastructure/server/application_protocol/http/Session.cpp \
	infrastructure/server/application_protocol/http/exceptions/error_lookup.cpp \
	infrastructure/server/application_protocol/http/exceptions/ReturnException.cpp \
	infrastructure/server/application_protocol/http/exceptions/Exception.cpp \
	infrastructure/server/application_protocol/http/core/Protocol.cpp \
	infrastructure/server/application_protocol/http/core/Context.cpp \
	infrastructure/server/application_protocol/http/presenters/success_lookup.cpp \
	infrastructure/server/application_protocol/http/presenters/get_listing_html.cpp \
	infrastructure/server/application_protocol/http/presenters/ServeStaticResourcePresenter.cpp \
	infrastructure/server/application_protocol/http/presenters/DeleteStaticResourcePresenter.cpp \
	infrastructure/server/application_protocol/http/methods.cpp \
	infrastructure/server/application_protocol/constants.cpp \
	infrastructure/server/application_protocol/TestProtocol.cpp \
	cgi/constants.cpp \
	cgi/Response.cpp \
	cgi/Exception.cpp \
	cgi/Parser.cpp \
	application/use_cases/serve_static_resource/ServeStaticResource.cpp \
	application/use_cases/delete_static_resource/DeleteStaticResource.cpp \
	application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.cpp \
	application/Exception.cpp \
	domain/entities/DynamicResource.cpp \
	domain/entities/StaticResource.cpp \
	domain/Exception.cpp \
	domain/value_objects/ResourceMetaData.cpp

# directories
SRC_DIR = src/
OBJ_DIR = .obj/

# files full paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
DEP = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.d))

NAME = webserv

CC = c++
#CFLAGS = -Wall -Wextra -MMD -MP -std=c++98 -g
CFLAGS = -Wall -Wextra -MMD -MP -std=c++98 -O3
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
