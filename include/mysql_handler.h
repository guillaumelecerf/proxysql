void mysql_session_init(mysql_session_t *);
void mysql_session_close(mysql_session_t *);
inline void client_COM_QUIT(mysql_session_t *);
inline void client_COM_INIT_DB(mysql_session_t *, pkt *);
inline void client_COM_QUERY(mysql_session_t *, pkt *);
inline void server_COM_QUIT(mysql_session_t *, pkt *, enum MySQL_response_type);
inline void server_COM_INIT_DB(mysql_session_t *, pkt *, enum MySQL_response_type);
inline void server_COM_QUERY(mysql_session_t *, pkt *, enum MySQL_response_type);
void process_mysql_server_pkts(mysql_session_t *);
int process_mysql_client_pkts(mysql_session_t *);
