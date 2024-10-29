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
