/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ed25519.h>
#include <string>
#include "crypto.hpp"
#include "hash.hpp"

namespace iroha {

  using sig_t = ed25519::sig_t;
  using pubkey_t = ed25519::pubkey_t;
  using privkey_t = ed25519::privkey_t;
  using keypair_t = ed25519::keypair_t;
  /**
   * Sign the message
   */
  sig_t sign(const uint8_t *msg, size_t msgsize, const pubkey_t &pub,
             const privkey_t &priv) {
    sig_t sig;
    ed25519_sign(sig.data(), msg, msgsize, pub.data(), priv.data());
    return sig;
  }

  /**
   * Verify signature
   */
  bool verify(const uint8_t *msg, size_t msgsize, const pubkey_t &pub,
              const sig_t &sig) {
    return 1 == ed25519_verify(sig.data(), msg, msgsize, pub.data());
  }

  /**
   * Generate seed
   */
  blob_t<32> create_seed() {
    blob_t<32> seed;
    ed25519_create_seed(seed.data());
    return seed;
  }

  /**
   * Generate 32 bytes seed based on a passphrase
   * @param passphrase
   * @return
   */
  blob_t<32> create_seed(std::string passphrase) {
    return sha3_256((uint8_t *)passphrase.data(), passphrase.size());
  }

  /**
   * Create keypair
   */
  keypair_t create_keypair(blob_t<32> seed) {
    pubkey_t pub;
    privkey_t priv;

    ed25519_create_keypair(pub.data(), priv.data(), seed.data());

    return keypair_t{.pubkey = pub, .privkey = priv};
  }
}
