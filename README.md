# kernel-driver-base
- a simple kernel driver base i made in around 15 minutes
- includes a simple ntoskrnl importer library to call functions without having them in your IAT

# current-functions
- safe attach ( still wouldnt use it to attach to AC protected processes )
- read / write
- get eprocess
- get base address ( eprocess + 0x520 ) 
- get cr3 ( eprocess + 0x28 )

# credits
- credit to @vmstruct for the ntoskrnl importer

# eac-bypass
- still failing to code a eac bypass? sure im here for you!
- i would sell you fully custom 1:1 driver or bootkit of your choice, prices start from $200 -> $1000
- if you are interested dm me on telegram: t.me/mmcopymemory

