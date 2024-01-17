sudo /usr/src/linux-headers-$(uname -r)/scripts/sign-file sha256 \
  /var/lib/shim-signed/mok/MOK.priv								               \
  /var/lib/shim-signed/mok/MOK.der                               \
  ./po_dev.ko

sudo /usr/src/linux-headers-$(uname -r)/scripts/sign-file sha256 \
  /var/lib/shim-signed/mok/MOK.priv                              \
  /var/lib/shim-signed/mok/MOK.der                               \
  ./popcorn.ko