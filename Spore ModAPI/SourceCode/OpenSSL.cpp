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


}
