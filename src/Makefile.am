DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

DANKCOIN_CONFIG_INCLUDES=-I$(builddir)/config
DANKCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

DANKCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
DANKCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

LIBDANKCOIN_SERVER=libdankcoin_server.a
LIBDANKCOIN_COMMON=libdankcoin_common.a
LIBDANKCOIN_CONSENSUS=libdankcoin_consensus.a
LIBDANKCOIN_CLI=libdankcoin_cli.a
LIBDANKCOIN_UTIL=libdankcoin_util.a
LIBDANKCOIN_CRYPTO=crypto/libdankcoin_crypto.a
LIBDANKCOINQT=qt/libdankcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBDANKCOIN_ZMQ=libdankcoin_zmq.a
endif
if BUILD_DANKCOIN_LIBS
LIBDANKCOINCONSENSUS=libdankcoinconsensus.la
endif
if ENABLE_WALLET
LIBDANKCOIN_WALLET=libdankcoin_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBDANKCOIN_CRYPTO) \
  $(LIBDANKCOIN_UTIL) \
  $(LIBDANKCOIN_COMMON) \
  $(LIBDANKCOIN_CONSENSUS) \
  $(LIBDANKCOIN_SERVER) \
  $(LIBDANKCOIN_CLI) \
  $(LIBDANKCOIN_WALLET) \
  $(LIBDANKCOIN_ZMQ)

lib_LTLIBRARIES = $(LIBDANKCOINCONSENSUS)

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_DANKCOIND
  bin_PROGRAMS += dankcoind
endif

if BUILD_DANKCOIN_UTILS
  bin_PROGRAMS += dankcoin-cli dankcoin-tx
endif

.PHONY: FORCE check-symbols check-security
# dankcoin core #
DANKCOIN_CORE_H = \
  addressindex.h \
  spentindex.h \
  timestampindex.h \
  addrman.h \
  base58.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  core_io.h \
  core_memusage.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  random.h \
  reverselock.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validationinterface.h \
  versionbits.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libdankcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between dankcoind and dankcoin-qt
libdankcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libdankcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdankcoin_server_a_SOURCES = \
  addrman.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(DANKCOIN_CORE_H)

if ENABLE_ZMQ
libdankcoin_zmq_a_CPPFLAGS = $(DANKCOIN_INCLUDES) $(ZMQ_CFLAGS)
libdankcoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdankcoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between dankcoind and dankcoin-qt, but only linked
# when wallet enabled
libdankcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_INCLUDES)
libdankcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdankcoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  policy/rbf.cpp \
  $(DANKCOIN_CORE_H)

# crypto primitives library
crypto_libdankcoin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_CONFIG_INCLUDES)
crypto_libdankcoin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libdankcoin_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# consensus: shared between all executables that validate any consensus rules.
libdankcoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_INCLUDES)
libdankcoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdankcoin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/dankcoinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between dankcoind, and dankcoin-qt and non-server tools
libdankcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_INCLUDES)
libdankcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdankcoin_common_a_SOURCES = \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(DANKCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libdankcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_INCLUDES)
libdankcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdankcoin_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(DANKCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libdankcoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between dankcoin-cli and dankcoin-qt
libdankcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_INCLUDES)
libdankcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libdankcoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(DANKCOIN_CORE_H)

nodist_libdankcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# dankcoind binary #
dankcoind_SOURCES = dankcoind.cpp
dankcoind_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_INCLUDES)
dankcoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
dankcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
dankcoind_SOURCES += dankcoind-res.rc
endif

dankcoind_LDADD = \
  $(LIBDANKCOIN_SERVER) \
  $(LIBDANKCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBDANKCOIN_UTIL) \
  $(LIBDANKCOIN_WALLET) \
  $(LIBDANKCOIN_ZMQ) \
  $(LIBDANKCOIN_CONSENSUS) \
  $(LIBDANKCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

dankcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# dankcoin-cli binary #
dankcoin_cli_SOURCES = dankcoin-cli.cpp
dankcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_INCLUDES) $(EVENT_CFLAGS)
dankcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
dankcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
dankcoin_cli_SOURCES += dankcoin-cli-res.rc
endif

dankcoin_cli_LDADD = \
  $(LIBDANKCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBDANKCOIN_UTIL) \
  $(LIBDANKCOIN_CRYPTO)

dankcoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# dankcoin-tx binary #
dankcoin_tx_SOURCES = dankcoin-tx.cpp
dankcoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(DANKCOIN_INCLUDES)
dankcoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
dankcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
dankcoin_tx_SOURCES += dankcoin-tx-res.rc
endif

dankcoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBDANKCOIN_COMMON) \
  $(LIBDANKCOIN_UTIL) \
  $(LIBDANKCOIN_CONSENSUS) \
  $(LIBDANKCOIN_CRYPTO) \
  $(LIBSECP256K1)

dankcoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# dankcoinconsensus library #
if BUILD_DANKCOIN_LIBS
include_HEADERS = script/dankcoinconsensus.h
libdankcoinconsensus_la_SOURCES = $(crypto_libdankcoin_crypto_a_SOURCES) $(libdankcoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libdankcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libdankcoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libdankcoinconsensus_la_LIBADD = $(LIBSECP256K1)
libdankcoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_DANKCOIN_INTERNAL
libdankcoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = $(CTAES_DIST)

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
