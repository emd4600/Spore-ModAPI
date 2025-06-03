/****************************************************************************
* Copyright (C) 2024 Rosalie Wanders
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once

#include <Spore\Internal.h>

namespace OpenSSL
{
	typedef void SSL;
	typedef void SSL_CTX;
	typedef void SSL_METHOD;
	typedef void DH;
	typedef void X509_STORE_CTX;
	typedef void SSL_SESSION;
	typedef void X509;
	typedef void BIO;
	typedef void CERT;
	typedef void SESS_CERT;
	typedef void ERR_STATE;
	typedef void BIO_METHOD;
	typedef void CRYPTO_EX_DATA;
	typedef void CRYPTO_dynlock_value;
	//typedef void STACK;
	typedef void X509_LOOKUP_METHOD;
	typedef void X509_LOOKUP;
	typedef void X509_STORE;
	typedef void X509_VERIFY_PARAM;

	int  SSL_accept(SSL* ssl);
	int  SSL_clear(SSL* ssl);
	int  SSL_connect(SSL* ssl);
	long SSL_ctrl(SSL* ssl,int cmd, long larg, void* parg);
	long SSL_CTX_ctrl(SSL_CTX* ctx, int cmd, long larg, void* parg);
	void SSL_CTX_free(SSL_CTX* ctx);
	int  SSL_CTX_load_verify_locations(SSL_CTX* ctx, const char* CAfile, const char* CApath);
	SSL_CTX* SSL_CTX_new(SSL_METHOD* meth);
	int	 SSL_CTX_set_cipher_list(SSL_CTX* ctx, const char* str);
	void SSL_CTX_set_tmp_dh_callback(SSL_CTX* ctx, DH *(*dh)(SSL* ssl, int is_export, int keylength));
	void SSL_CTX_set_verify(SSL_CTX* ctx, int mode, int (*callback)(int, X509_STORE_CTX*));
	void SSL_CTX_set_verify_depth(SSL_CTX* ctx, int depth);
	void SSL_free(SSL* ssl);
	SSL_SESSION* SSL_get1_session(SSL* ssl);
	int	  SSL_get_error(const SSL* s, int ret_code);
	X509* SSL_get_peer_certificate(const SSL* s);
	int   SSL_get_shutdown(const SSL* ssl);
	int   SSL_library_init(void);
	SSL*  SSL_new(SSL_CTX* ctx);
	int   SSL_read(SSL* ssl,void* buf,int num);
	void  SSL_SESSION_free(SSL_SESSION* ses);
	SSL_SESSION* SSL_SESSION_new(void);
	void  SSL_set_bio(SSL* s, BIO* rbio, BIO* wbio);
	int	  SSL_set_session(SSL* to, SSL_SESSION* session);
	int   SSL_shutdown(SSL* s);
	int   SSL_write(SSL* ssl,const void* buf,int num);
	SSL_METHOD* SSLv23_client_method(void);
	SSL_METHOD* SSLv23_method(void);
	SSL_METHOD* SSLv23_server_method(void);

	void ssl_cert_free(CERT* c);
	int  ssl_clear_bad_session(SSL* s);
	void ssl_clear_cipher_ctx(SSL* s);
	int  ssl_get_new_session(SSL* s, int session);
	int  ssl_init_wbio_buffer(SSL* s, int push);
	void ssl_load_ciphers(void);
	void ssl_sess_cert_free(SESS_CERT* sc);
	void ssleay_rand_add(const void* buf, int num, double add);

	typedef int (*ERR_print_errors_cb_func)(const char* str, size_t len, void* u);
	void ERR_clear_error(void);
	void ERR_error_string_n(unsigned long e, char* buf, size_t len);
	ERR_STATE* ERR_get_state(void);
	void ERR_print_errors_cb(ERR_print_errors_cb_func cb, void* u);
	void ERR_put_error(int lib, int func, int reason, const char* file, int line);
	void ERR_set_error_data(char* data, int flags);

	void OPENSSL_add_all_algorithms_noconf(void);
	void OpenSSL_add_all_ciphers(void);
	void OpenSSL_add_all_digests(void);
	void OPENSSL_cleanse(void* ptr, size_t len);
	void OPENSSL_free(void* ptr);
	// TODO: void OPENSSL_showfatal(const char* fmta, ...);
	void OpenSSLDie(const char* file, int line, const char* assertion);

	long BIO_ctrl(BIO* b, int cmd, long larg, void* parg);
	BIO_METHOD* BIO_f_buffer(void);
	int  BIO_free(BIO* a);
	void BIO_free_all(BIO* bio);
	int  BIO_gets(BIO* b, char* in, int inl);
	long BIO_int_ctrl(BIO* b, int cmd, long larg, int iarg);
	BIO* BIO_new(BIO_METHOD* method);
	BIO* BIO_new_file(const char* filename, const char* mode);
	BIO* BIO_new_mem_buf(void* buf, int len);
	BIO* BIO_pop(BIO* b);
	BIO* BIO_push(BIO* b, BIO* append);
	int	 BIO_puts(BIO* bp, const char* buf);
	int	 BIO_read(BIO* b, void* data, int len);
	int  BIO_write(BIO* b, const void* data, int len);

	int  CRYPTO_add_lock(int* pointer, int amount, int type, const char* file, int line);
	void CRYPTO_free_ex_data(int class_index, void* obj, CRYPTO_EX_DATA* ad);
	CRYPTO_dynlock_value* CRYPTO_get_dynlock_value(int i);
	void CRYPTO_lock(int mode, int type, const char* file, int line);
	void* CRYPTO_malloc(int num, const char* file, int line);
	int  CRYPTO_num_locks(void);
	void CRYPTO_set_dynlock_create_callback(CRYPTO_dynlock_value* (*func)(const char* file, int line));
	void CRYPTO_set_dynlock_destroy_callback(void (*func)(CRYPTO_dynlock_value* l, const char* file, int line));
	void CRYPTO_set_dynlock_lock_callback(void (*func)(int mode, CRYPTO_dynlock_value* l, const char* file, int line));
	void CRYPTO_set_id_callback(unsigned long (*func)(void));
	void CRYPTO_set_locking_callback(void (*func)(int mode, int type, const char* file, int line));
	int  CRYPTO_set_mem_functions(void* (*m)(size_t), void* (*r)(void*, size_t), void (*f)(void*));

	// TODO: void sk_free(STACK* st);
	// TODO: sk_X509_NAME_pop_free
	int  i2d_X509(X509* x, unsigned char** out);
	void X509_free(X509* a);
	X509_LOOKUP_METHOD* X509_LOOKUP_file(void);
	X509_LOOKUP_METHOD* X509_LOOKUP_hash_dir(void);
	// TODO: X509_LOOKUP_load_file
	X509_LOOKUP* X509_STORE_add_lookup(X509_STORE* v, X509_LOOKUP_METHOD* m);
	int	 X509_STORE_load_locations(X509_STORE* ctx, const char* file, const char* dir);
	void X509_VERIFY_PARAM_free(X509_VERIFY_PARAM* param);
}

namespace Addresses(OpenSSL)
{
	DeclareAddress(SSL_accept);
	DeclareAddress(SSL_clear);
	DeclareAddress(SSL_connect);
	DeclareAddress(SSL_ctrl);
	DeclareAddress(SSL_CTX_ctrl);
	DeclareAddress(SSL_CTX_free);
	DeclareAddress(SSL_CTX_load_verify_locations);
	DeclareAddress(SSL_CTX_new);
	DeclareAddress(SSL_CTX_set_cipher_list);
	DeclareAddress(SSL_CTX_set_tmp_dh_callback);
	DeclareAddress(SSL_CTX_set_verify);
	DeclareAddress(SSL_CTX_set_verify_depth);
	DeclareAddress(SSL_free);
	DeclareAddress(SSL_get1_session);
	DeclareAddress(SSL_get_error);
	DeclareAddress(SSL_get_peer_certificate);
	DeclareAddress(SSL_get_shutdown);
	DeclareAddress(SSL_library_init);
	DeclareAddress(SSL_new);
	DeclareAddress(SSL_read);
	DeclareAddress(SSL_SESSION_free);
	DeclareAddress(SSL_SESSION_new);
	DeclareAddress(SSL_set_bio);
	DeclareAddress(SSL_set_session);
	DeclareAddress(SSL_shutdown);
	DeclareAddress(SSL_write);
	DeclareAddress(SSLv23_client_method);
	DeclareAddress(SSLv23_method);
	DeclareAddress(SSLv23_server_method);

	DeclareAddress(sk_SSL_CIPHER_free);
	DeclareAddress(ssl_cert_free);
	DeclareAddress(ssl_clear_bad_session);
	DeclareAddress(ssl_clear_cipher_ctx);
	DeclareAddress(ssl_get_new_session);
	DeclareAddress(ssl_init_wbio_buffer);
	DeclareAddress(ssl_load_ciphers);
	DeclareAddress(ssl_sess_cert_free);
	DeclareAddress(ssleay_rand_add);

	DeclareAddress(ERR_clear_error);
	DeclareAddress(ERR_error_string_n);
	DeclareAddress(ERR_get_state);
	DeclareAddress(ERR_print_errors_cb);
	DeclareAddress(ERR_put_error);
	DeclareAddress(ERR_set_error_data);

	DeclareAddress(OPENSSL_add_all_algorithms_noconf);
	DeclareAddress(OpenSSL_add_all_ciphers);
	DeclareAddress(OpenSSL_add_all_digests);
	DeclareAddress(OPENSSL_cleanse);
	DeclareAddress(OPENSSL_free);
	DeclareAddress(OPENSSL_showfatal);
	DeclareAddress(OpenSSLDie);

	DeclareAddress(BIO_ctrl);
	DeclareAddress(BIO_f_buffer);
	DeclareAddress(BIO_free);
	DeclareAddress(BIO_free_all);
	DeclareAddress(BIO_gets);
	DeclareAddress(BIO_int_ctrl);
	DeclareAddress(BIO_new);
	DeclareAddress(BIO_new_file);
	DeclareAddress(BIO_new_mem_buf);
	DeclareAddress(BIO_pop);
	DeclareAddress(BIO_push);
	DeclareAddress(BIO_puts);
	DeclareAddress(BIO_read);
	DeclareAddress(BIO_write);

	DeclareAddress(CRYPTO_add_lock);
	DeclareAddress(CRYPTO_free_ex_data);
	DeclareAddress(CRYPTO_get_dynlock_value);
	DeclareAddress(CRYPTO_lock);
	DeclareAddress(CRYPTO_malloc);
	DeclareAddress(CRYPTO_num_locks);
	DeclareAddress(CRYPTO_set_dynlock_create_callback);
	DeclareAddress(CRYPTO_set_dynlock_destroy_callback);
	DeclareAddress(CRYPTO_set_dynlock_lock_callback);
	DeclareAddress(CRYPTO_set_id_callback);
	DeclareAddress(CRYPTO_set_locking_callback);
	DeclareAddress(CRYPTO_set_mem_functions);

	DeclareAddress(sk_X509_NAME_pop_free);
	DeclareAddress(i2d_X509);
	DeclareAddress(X509_free);
	DeclareAddress(X509_LOOKUP_file);
	DeclareAddress(X509_LOOKUP_hash_dir);
	DeclareAddress(X509_LOOKUP_load_file);
	DeclareAddress(X509_STORE_add_lookup);
	DeclareAddress(X509_STORE_load_locations);
	DeclareAddress(X509_VERIFY_PARAM_free);
}
