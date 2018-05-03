Shared Libraries
================

## mb8coinconsensus

The purpose of this library is to make the verification functionality that is critical to MB8Coin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `mb8coinconsensus.h` located in  `src/script/mb8coinconsensus.h`.

#### Version

`mb8coinconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`mb8coinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `mb8coinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `mb8coinconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `mb8coinconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/mb8coin/bips/blob/master/bip-0016.mediawiki)) subscripts
- `mb8coinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/mb8coin/bips/blob/master/bip-0066.mediawiki)) compliance

##### Errors
- `mb8coinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `mb8coinconsensus_verify_script` for the verification status)*
- `mb8coinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `mb8coinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `mb8coinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`

### Example Implementations
- [NMB8Coin](https://github.com/NicolasDorier/NMB8Coin/blob/master/NMB8Coin/Script.cs#L814) (.NET Bindings)
- [node-libmb8coinconsensus](https://github.com/bitpay/node-libmb8coinconsensus) (Node.js Bindings)
- [java-libmb8coinconsensus](https://github.com/dexX7/java-libmb8coinconsensus) (Java Bindings)
- [mb8coinconsensus-php](https://github.com/Bit-Wasp/mb8coinconsensus-php) (PHP Bindings)
