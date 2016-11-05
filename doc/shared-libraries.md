Shared Libraries
================

## dankcoinconsensus

The purpose of this library is to make the verification functionality that is critical to Dankcoin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `dankcoinconsensus.h` located in  `src/script/dankcoinconsensus.h`.

#### Version

`dankcoinconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`dankcoinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `dankcoinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `dankcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `dankcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/dankcoin/bips/blob/master/bip-0016.mediawiki)) subscripts
- `dankcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/dankcoin/bips/blob/master/bip-0066.mediawiki)) compliance

##### Errors
- `dankcoinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `dankcoinconsensus_verify_script` for the verification status)*
- `dankcoinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `dankcoinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `dankcoinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`

### Example Implementations
- [NDankcoin](https://github.com/NicolasDorier/NDankcoin/blob/master/NDankcoin/Script.cs#L814) (.NET Bindings)
- [node-libdankcoinconsensus](https://github.com/bitpay/node-libdankcoinconsensus) (Node.js Bindings)
- [java-libdankcoinconsensus](https://github.com/dexX7/java-libdankcoinconsensus) (Java Bindings)
- [dankcoinconsensus-php](https://github.com/Bit-Wasp/dankcoinconsensus-php) (PHP Bindings)
