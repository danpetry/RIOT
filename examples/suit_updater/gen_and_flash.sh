# usage: generate_keys_and_flash.sh <board name>
make -C ../../dist/tools/firmware
../../dist/tools/firmware/bin/firmware genkeys sec.key pub.key
BOARD=$1 APP_VER=$(date +%s) make -j4 clean riotboot
BOARD=$1 APP_VER=$(date +%s) make -j4 riotboot/flash

# upload firmware and get hex
read -p "Please rename and upload your firmware, and input the new firmware name:" firmwarename
read -p "and now the truncated SHA1 from the riot-labs website:" firmwareSHA
python3 gen_manifest.py -u repo.riot-labs.de/$firmwareSHA -k ../../dist/tools/firmware/sec.key -o manifest.cbor bin/$1/$firmwarename
make term BOARD=$1

