#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"

#include <Spore\OpenSSL.h>

namespace Addresses(OpenSSL)
{
	DefineAddress(SSL_accept, SelectAddress(0x0117f590, 0x0117ce10));
	DefineAddress(SSL_clear, SelectAddress(0x0117ebe0, 0x0117c460));
	DefineAddress(SSL_connect, SelectAddress(0x0117f5d0, 0x0117ce50));
	DefineAddress(SSL_ctrl, SelectAddress(0x0117f0e0, 0x0117c960));
	DefineAddress(SSL_CTX_ctrl, SelectAddress(0x0117dca0, 0x0117b520));
	DefineAddress(SSL_CTX_free, SelectAddress(0x0117e1b0, 0x0117ba30));
	DefineAddress(SSL_CTX_load_verify_locations, SelectAddress(0x0117eb90, 0x0117c410));
	DefineAddress(SSL_CTX_new, SelectAddress(0x0117f200, 0x0117ca80));
	DefineAddress(SSL_CTX_set_cipher_list, SelectAddress(0x0117df20, 0x0117b7a0));
	DefineAddress(SSL_CTX_set_tmp_dh_callback, SelectAddress(0x0117ebc0, 0x0117c440));
	DefineAddress(SSL_CTX_set_verify, SelectAddress(0x0117e2b0, 0x0117bb30));
	DefineAddress(SSL_CTX_set_verify_depth, SelectAddress(0x0117e2d0, 0x0117bb50));
	DefineAddress(SSL_free, SelectAddress(0x0117ef30, 0x0117c7b0));
	DefineAddress(SSL_get1_session, SelectAddress(0x01183db0, 0x01181640));
	DefineAddress(SSL_get_error, SelectAddress(0x0117f470, 0x0117ccf0));
	DefineAddress(SSL_get_peer_certificate, SelectAddress(0x0117db60, 0x0117b3e0));
	DefineAddress(SSL_get_shutdown, SelectAddress(0x011b4600, 0x011b1e70));
	DefineAddress(SSL_library_init, SelectAddress(0x01185980, 0x01183210));
	DefineAddress(SSL_new, SelectAddress(0x0117ed00, 0x0117c580));
	DefineAddress(SSL_read, SelectAddress(0x0117dbb0, 0x0117b430));
	DefineAddress(SSL_SESSION_free, SelectAddress(0x01183ee0, 0x01181770));
	DefineAddress(SSL_SESSION_new, SelectAddress(0x01183df0, 0x01181680));
	DefineAddress(SSL_set_bio, SelectAddress(0x0117daf0, 0x0117b370));
	DefineAddress(SSL_set_session, SelectAddress(0x01183fa0, 0x01181830));
	DefineAddress(SSL_shutdown, SelectAddress(0x0117f090, 0x0117c910));
	DefineAddress(SSL_write, SelectAddress(0x0117dc40, 0x0117b4c0));
	DefineAddress(SSLv23_client_method, SelectAddress(0x01185240, 0x01182ad0));
	DefineAddress(SSLv23_method, SelectAddress(0x01185960, 0x011831f0));
	DefineAddress(SSLv23_server_method, SelectAddress(0x01185930, 0x011831c0));

	DefineAddress(ssl_cert_free, SelectAddress(0x01197300, 0x01194b90));
	DefineAddress(ssl_clear_bad_session, SelectAddress(0x01184680, 0x01181f10));
	DefineAddress(ssl_clear_cipher_ctx, SelectAddress(0x0117ea20, 0x0117c2a0));
	DefineAddress(ssl_get_new_session, SelectAddress(0x011841a0, 0x01181a30));
	DefineAddress(ssl_init_wbio_buffer, SelectAddress(0x0117eaa0, 0x0117c320));
	DefineAddress(ssl_load_ciphers, SelectAddress(0x01195610, 0x01192eb0));
	DefineAddress(ssl_sess_cert_free, SelectAddress(0x01197440, 0x01194cd0));
	DefineAddress(ssleay_rand_add, SelectAddress(0x01188050, 0x011858c0));

	DefineAddress(ERR_clear_error, SelectAddress(0x011835d0, 0x01180e60));
	DefineAddress(ERR_error_string_n, SelectAddress(0x01183640, 0x01180ed0));
	DefineAddress(ERR_get_state, SelectAddress(0x01183060, 0x011808f0));
	DefineAddress(ERR_print_errors_cb, SelectAddress(0x011d1300, 0x011cec10));
	DefineAddress(ERR_put_error, SelectAddress(0x011834e0, 0x01180d70));
	DefineAddress(ERR_set_error_data, SelectAddress(0x01183170, 0x01180a00));

	DefineAddress(OPENSSL_add_all_algorithms_noconf, SelectAddress(0x01185970, 0x01183200));
	DefineAddress(OpenSSL_add_all_ciphers, SelectAddress(0x011ab3d0, 0x011a8c70));
	DefineAddress(OpenSSL_add_all_digests, SelectAddress(0x011ab280, 0x011a8b20));
	DefineAddress(OPENSSL_cleanse, SelectAddress(0x01185fa0, 0x01183830));
	DefineAddress(OPENSSL_free, SelectAddress(0x01185d50, 0x011835e0));
	DefineAddress(OPENSSL_showfatal, SelectAddress(0x01183b80, 0x01181410));
	DefineAddress(OpenSSLDie, SelectAddress(0x01183ca0, 0x01181530));

	DefineAddress(BIO_ctrl, SelectAddress(0x01179a00, 0x011772a0));
	DefineAddress(BIO_f_buffer, SelectAddress(0x01199100, 0x01196990));
	DefineAddress(BIO_free, SelectAddress(0x011796b0, 0x01176f50));
	DefineAddress(BIO_free_all, SelectAddress(0x01179bc0, 0x01177460));
	DefineAddress(BIO_gets, SelectAddress(0x01179960, 0x01177200));
	DefineAddress(BIO_int_ctrl, SelectAddress(0x01179c60, 0x01177500));
	DefineAddress(BIO_new, SelectAddress(0x01179c10, 0x011774b0));
	DefineAddress(BIO_new_file, SelectAddress(0x0117d9e0, 0x0117b260));
	DefineAddress(BIO_new_mem_buf, SelectAddress(0x01179ca0, 0x01177540));
	DefineAddress(BIO_pop, SelectAddress(0x01179b70, 0x01177410));
	DefineAddress(BIO_push, SelectAddress(0x01179b20, 0x011773c0));
	DefineAddress(BIO_puts, SelectAddress(0x011798c0, 0x01177160));
	DefineAddress(BIO_read, SelectAddress(0x01179760, 0x01177000));
	DefineAddress(BIO_write, SelectAddress(0x01179810, 0x011770b0));

	DefineAddress(CRYPTO_add_lock, SelectAddress(0x01183d60, 0x011815f0));
	DefineAddress(CRYPTO_free_ex_data, SelectAddress(0x01186a70, 0x011842e0));
	DefineAddress(CRYPTO_get_dynlock_value, SelectAddress(0x011839c0, 0x01181250));
	DefineAddress(CRYPTO_lock, SelectAddress(0x01183cd0, 0x01181560));
	DefineAddress(CRYPTO_malloc, SelectAddress(0x01185ba0, 0x01183430));
	DefineAddress(CRYPTO_num_locks, SelectAddress(0x00a2f320, 0x0089cef0));
	DefineAddress(CRYPTO_set_dynlock_create_callback, SelectAddress(0x01183a40, 0x011812d0));
	DefineAddress(CRYPTO_set_dynlock_destroy_callback, SelectAddress(0x01183a60, 0x011812f0));
	DefineAddress(CRYPTO_set_dynlock_lock_callback, SelectAddress(0x01183a50, 0x011812e0));
	DefineAddress(CRYPTO_set_id_callback, SelectAddress(0x01183a80, 0x01181310));
	DefineAddress(CRYPTO_set_locking_callback, SelectAddress(0x01183a70, 0x01181300));
	DefineAddress(CRYPTO_set_mem_functions, SelectAddress(0x01185af0, 0x01183380));

	DefineAddress(sk_free, SelectAddress(0x01180560, 0x0117ddd0));
	DefineAddress(sk_X509_NAME_pop_free, SelectAddress(0x011807e0, 0x0117e050));
	DefineAddress(i2d_X509, SelectAddress(0x0117f700, 0x0117cf80));
	DefineAddress(X509_free, SelectAddress(0x0117f730, 0x0117cfb0));
	DefineAddress(X509_LOOKUP_file, SelectAddress(0x011b9f50, 0x011b7830));
	DefineAddress(X509_LOOKUP_hash_dir, SelectAddress(0x011b9990, 0x011b7270));
	DefineAddress(X509_LOOKUP_load_file, SelectAddress(0x01197b30, 0x011953c0));
	DefineAddress(X509_STORE_add_lookup, SelectAddress(0x01197d30, 0x011955c0));
	DefineAddress(X509_STORE_load_locations, SelectAddress(0x011999e0, 0x01197290));
	DefineAddress(X509_VERIFY_PARAM_free, SelectAddress(0x01196a80, 0x01194320));
}

#endif // MODAPI_DLL_EXPORT