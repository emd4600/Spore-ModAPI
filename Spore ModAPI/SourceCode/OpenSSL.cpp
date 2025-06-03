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
#include <Spore\OpenSSL.h>

namespace OpenSSL
{
	auto_STATIC_METHOD(OpenSSL, int, SSL_accept, Args(SSL* ssl), Args(ssl));
	auto_STATIC_METHOD(OpenSSL, int, SSL_clear, Args(SSL* ssl), Args(ssl));
	auto_STATIC_METHOD(OpenSSL, int, SSL_connect, Args(SSL* ssl), Args(ssl));
	auto_STATIC_METHOD(OpenSSL, long, SSL_ctrl, Args(SSL* ssl, int cmd, long larg, void* parg), Args(ssl, cmd, larg, parg));
	auto_STATIC_METHOD(OpenSSL, long, SSL_CTX_ctrl, Args(SSL_CTX* ctx, int cmd, long larg, void* parg), Args(ctx, cmd, larg, parg));
	auto_STATIC_METHOD(OpenSSL, void, SSL_CTX_free, Args(SSL_CTX* ctx), Args(ctx));
	auto_STATIC_METHOD(OpenSSL, int, SSL_CTX_load_verify_locations, Args(SSL_CTX* ctx, const char* CAfile, const char* CApath), Args(ctx, CAfile, CApath));
	auto_STATIC_METHOD(OpenSSL, SSL_CTX*, SSL_CTX_new, Args(SSL_METHOD* meth), Args(meth));
	auto_STATIC_METHOD(OpenSSL, int, SSL_CTX_set_cipher_list, Args(SSL_CTX* ctx, const char* str), Args(ctx, str));
	auto_STATIC_METHOD(OpenSSL, void, SSL_CTX_set_tmp_dh_callback, Args(SSL_CTX* ctx, DH* (*dh)(SSL* ssl, int is_export, int keylength)), Args(ctx, dh));
	auto_STATIC_METHOD(OpenSSL, void, SSL_CTX_set_verify, Args(SSL_CTX* ctx, int mode, int (*callback)(int, X509_STORE_CTX*)), Args(ctx, mode, callback));
	auto_STATIC_METHOD(OpenSSL, void, SSL_CTX_set_verify_depth, Args(SSL_CTX* ctx, int depth), Args(ctx, depth));
	auto_STATIC_METHOD(OpenSSL, void, SSL_free, Args(SSL* ssl), Args(ssl));
	auto_STATIC_METHOD(OpenSSL, SSL_SESSION*, SSL_get1_session, Args(SSL* ssl), Args(ssl));
	auto_STATIC_METHOD(OpenSSL, int, SSL_get_error, Args(const SSL* s, int ret_code), Args(s, ret_code));
	auto_STATIC_METHOD(OpenSSL, X509*, SSL_get_peer_certificate, Args(const SSL* s), Args(s));
	auto_STATIC_METHOD(OpenSSL, int, SSL_get_shutdown, Args(const SSL* ssl), Args(ssl));
	auto_STATIC_METHOD(OpenSSL, int, SSL_library_init, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, SSL*, SSL_new, Args(SSL_CTX* ctx), Args(ctx));
	auto_STATIC_METHOD(OpenSSL, int, SSL_read, Args(SSL* ssl, void* buf, int num), Args(ssl, buf, num));
	auto_STATIC_METHOD(OpenSSL, void, SSL_SESSION_free, Args(SSL_SESSION* ses), Args(ses));
	auto_STATIC_METHOD(OpenSSL, SSL_SESSION*, SSL_SESSION_new, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, void, SSL_set_bio, Args(SSL* s, BIO* rbio, BIO* wbio), Args(s, rbio, wbio));
	auto_STATIC_METHOD(OpenSSL, int, SSL_set_session, Args(SSL* to, SSL_SESSION* session), Args(to, session));
	auto_STATIC_METHOD(OpenSSL, int, SSL_shutdown, Args(SSL* s), Args(s));
	auto_STATIC_METHOD(OpenSSL, int, SSL_write, Args(SSL* ssl, const void* buf, int num), Args(ssl, buf, num));
	auto_STATIC_METHOD(OpenSSL, SSL_METHOD*, SSLv23_client_method, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, SSL_METHOD*, SSLv23_method, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, SSL_METHOD*, SSLv23_server_method, Args(void), Args());

	auto_STATIC_METHOD(OpenSSL, void, ssl_cert_free, Args(CERT* c), Args(c));
	auto_STATIC_METHOD(OpenSSL, int, ssl_clear_bad_session, Args(SSL* s), Args(s));
	auto_STATIC_METHOD(OpenSSL, void, ssl_clear_cipher_ctx, Args(SSL* s), Args(s));
	auto_STATIC_METHOD(OpenSSL, int, ssl_get_new_session, Args(SSL* s, int session), Args(s, session));
	auto_STATIC_METHOD(OpenSSL, int, ssl_init_wbio_buffer, Args(SSL* s, int push), Args(s, push));
	auto_STATIC_METHOD(OpenSSL, void, ssl_load_ciphers, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, void, ssl_sess_cert_free, Args(SESS_CERT* sc), Args(sc));
	auto_STATIC_METHOD(OpenSSL, void, ssleay_rand_add, Args(const void* buf, int num, double add), Args(buf, num, add));

	auto_STATIC_METHOD(OpenSSL, void, ERR_clear_error, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, void, ERR_error_string_n, Args(unsigned long e, char* buf, size_t len), Args(e, buf, len));
	auto_STATIC_METHOD(OpenSSL, ERR_STATE*, ERR_get_state, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, void, ERR_print_errors_cb, Args(ERR_print_errors_cb_func cb, void* u), Args(cb, u));
	auto_STATIC_METHOD(OpenSSL, void, ERR_put_error, Args(int lib, int func, int reason, const char* file, int line), Args(lib, func, reason, file, line));
	auto_STATIC_METHOD(OpenSSL, void, ERR_set_error_data, Args(char* data, int flags), Args(data, flags));

	auto_STATIC_METHOD(OpenSSL, void, OPENSSL_add_all_algorithms_noconf, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, void, OpenSSL_add_all_ciphers, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, void, OpenSSL_add_all_digests, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, void, OPENSSL_cleanse, Args(void* ptr, size_t len), Args(ptr, len));
	auto_STATIC_METHOD(OpenSSL, void, OPENSSL_free, Args(void* ptr), Args(ptr));
	// TODO: auto_STATIC_METHOD(OpenSSL, void, OPENSSL_showfatal, Args(const char* fmta, ...), Args(fmta, __VA_ARGS__));
	auto_STATIC_METHOD(OpenSSL, void, OpenSSLDie, Args(const char* file, int line, const char* assertion), Args(file, line, assertion));

	auto_STATIC_METHOD(OpenSSL, long, BIO_ctrl, Args(BIO* b, int cmd, long larg, void* parg), Args(b, cmd, larg, parg));
	auto_STATIC_METHOD(OpenSSL, BIO_METHOD*, BIO_f_buffer, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, int, BIO_free, Args(BIO* a), Args(a));
	auto_STATIC_METHOD(OpenSSL, void, BIO_free_all, Args(BIO* bio), Args(bio));
	auto_STATIC_METHOD(OpenSSL, int, BIO_gets, Args(BIO* b, char* in, int inl), Args(b, in, inl));
	auto_STATIC_METHOD(OpenSSL, long, BIO_int_ctrl, Args(BIO* b, int cmd, long larg, int iarg), Args(b, cmd, larg, iarg));
	auto_STATIC_METHOD(OpenSSL, BIO*, BIO_new, Args(BIO_METHOD* method), Args(method));
	auto_STATIC_METHOD(OpenSSL, BIO*, BIO_new_file, Args(const char* filename, const char* mode), Args(filename, mode));
	auto_STATIC_METHOD(OpenSSL, BIO*, BIO_new_mem_buf, Args(void* buf, int len), Args(buf, len));
	auto_STATIC_METHOD(OpenSSL, BIO*, BIO_pop, Args(BIO* b), Args(b));
	auto_STATIC_METHOD(OpenSSL, BIO*, BIO_push, Args(BIO* b, BIO* append), Args(b, append));
	auto_STATIC_METHOD(OpenSSL, int, BIO_puts, Args(BIO* bp, const char* buf), Args(bp, buf));
	auto_STATIC_METHOD(OpenSSL, int, BIO_read, Args(BIO* b, void* data, int len), Args(b, data, len));
	auto_STATIC_METHOD(OpenSSL, int, BIO_write, Args(BIO* b, const void* data, int len), Args(b, data, len));

	auto_STATIC_METHOD(OpenSSL, int, CRYPTO_add_lock, Args(int* pointer, int amount, int type, const char* file, int line), Args(pointer, amount, type, file, line));
	auto_STATIC_METHOD(OpenSSL, void, CRYPTO_free_ex_data, Args(int class_index, void* obj, CRYPTO_EX_DATA* ad), Args(class_index, obj, ad));
	auto_STATIC_METHOD(OpenSSL, CRYPTO_dynlock_value*, CRYPTO_get_dynlock_value, Args(int i), Args(i));
	auto_STATIC_METHOD(OpenSSL, void, CRYPTO_lock, Args(int mode, int type, const char* file, int line), Args(mode, type, file, line));
	auto_STATIC_METHOD(OpenSSL, void*, CRYPTO_malloc, Args(int num, const char* file, int line), Args(num, file, line));
	auto_STATIC_METHOD(OpenSSL, int, CRYPTO_num_locks, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, void, CRYPTO_set_dynlock_create_callback, Args(CRYPTO_dynlock_value* (*func)(const char* file, int line)), Args(func));
	auto_STATIC_METHOD(OpenSSL, void, CRYPTO_set_dynlock_destroy_callback, Args(void (*func)(CRYPTO_dynlock_value* l, const char* file, int line)), Args(func));
	auto_STATIC_METHOD(OpenSSL, void, CRYPTO_set_dynlock_lock_callback, Args(void (*func)(int mode, CRYPTO_dynlock_value* l, const char* file, int line)), Args(func));
	auto_STATIC_METHOD(OpenSSL, void, CRYPTO_set_id_callback, Args(unsigned long (*func)(void)), Args(func));
	auto_STATIC_METHOD(OpenSSL, void, CRYPTO_set_locking_callback, Args(void (*func)(int mode, int type, const char* file, int line)), Args(func));
	auto_STATIC_METHOD(OpenSSL, int, CRYPTO_set_mem_functions, Args(void* (*m)(size_t), void* (*r)(void*, size_t), void (*f)(void*)), Args(m, r, f));

	// TODO: auto_STATIC_METHOD(OpenSSL, void, sk_free, Args(STACK* st), Args(st));
	// TODO: sk_X509_NAME_pop_free
	auto_STATIC_METHOD(OpenSSL, int, i2d_X509, Args(X509* x, unsigned char** out), Args(x, out));
	auto_STATIC_METHOD(OpenSSL, void, X509_free, Args(X509* a), Args(a));
	auto_STATIC_METHOD(OpenSSL, X509_LOOKUP_METHOD*, X509_LOOKUP_file, Args(void), Args());
	auto_STATIC_METHOD(OpenSSL, X509_LOOKUP_METHOD*, X509_LOOKUP_hash_dir, Args(void), Args());
	// TODO: X509_LOOKUP_load_file
	auto_STATIC_METHOD(OpenSSL, X509_LOOKUP*, X509_STORE_add_lookup, Args(X509_STORE* v, X509_LOOKUP_METHOD* m), Args(v, m));
	auto_STATIC_METHOD(OpenSSL, int, X509_STORE_load_locations, Args(X509_STORE* ctx, const char* file, const char* dir), Args(ctx, file, dir));
	auto_STATIC_METHOD(OpenSSL, void, X509_VERIFY_PARAM_free, Args(X509_VERIFY_PARAM* param), Args(param));
}
