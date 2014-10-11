var logoNames = ["3COM", "ABIT", "ACER", "A-DATA", "ADATA", "AEXEA", "ALI", "AMD", "AMI", "AOC", "AOPEN",
                             "APACER", "APPLE", "ASINT", "ASROCK", "ASUS", "ASZ", "ATHEROS", "ATI", "AUO", "AUTHENTEC",
                             "AVAGO", "AVEO", "B&DATA", "BENQ", "BIOSTAR", "B-LINK", "BROADCOM", "CANON", "CHAINTECH",
                             "CHICONY", "CISCO", "COLORFUL", "COMEON", "CORSAIR", "CREATIVE", "DELL", "DFI", "D-LINK",
                             "DTK", "EAGET", "EAST", "ECS", "ELEPHANT", "ELIXIR", "ELSA", "EMPIA", "E-MU", "ENLON",
                             "ENNYAH", "ETRON", "EXCELSTOR", "FIC", "FOUNDER", "FUJITSU", "GAINWARO", "GALAXY", "GAMEN",
                             "GEIL", "GIGABYTE", "GREAT WALL", "G.SKILL", "HASEE", "HITACHI", "HOMKEY", "HP","HYNIX", "HYUNDAI",
                             "IBM", "INNOVISION", "INTEL", "IOMEGA", "JETWAY", "J&W", "KINGBOX", "KINGFAST", "KINGMAX",
                             "KINGSPEC", "KINGSTEK", "KINGSTON", "KINGTIGER", "LEADTEK", "LENOVO", "LG", "LINKSYS",
                             "LITEON", "LITTLE TIGER","LOGITECH", "MACY", "MAGIC-PRO", "MARVELL", "MATROX", "M_AUDIO",
                             "MAXSUN", "MAXTOR", "MAYA", "MEGASTAR", "MICRON", "MICROSOFT", "MMC", "M-ONE", "MOTOROLA", "MSI",
                             "MUSILAND", "NEC", "NETGEAR", "NOKIA", "NVIDIA", "OCZ", "OMEGA", "OMNIVISION", "OMRON", "ONDA",
                             "ONKYO", "PANASONIC", "PHILIPS", "PHOENIX", "PINE", "PIONEER", "PIXART", "PLDS", "POWERCOLOR",
                             "PRIMAX", "QDI", "QIMONDA", "QUANTUM", "RALINK", "RAPOO", "RAZER", "REALTEK", "SAMSUNG", "SANYO",
                             "SAPPHIRE", "SEAGATE", "SHARK", "SIEMENS", "SIS", "SMP", "SONIX", "SONY", "SOYO", "SPARK", "SUNPLUS",
                             "SUPERGRAPHIC", "SUPOX", "SYMBOL", "SYNTEK", "TAIYANFA", "TDK", "TEKRAM", "TERRATEC", "TEXAS",
                             "TONGFANG", "TOSHIBA", "TOYOTA", "TP-LINK", "TRANSMETA", "TRUST", "TSSTCORP", "T&W", "TYAN", "UMC",
                             "UNIKA", "VIA", "VIMICRO", "VIRTUALBOX", "WDC", "WINBOND", "XFX", "YESTON", "ZOTAC", "ZTE"];


var distrowatchNames = ["mint", "ubuntu", "debian", "mageia", "fedora", "suse", "arch", "elementary", "zorin", "centos",
                             "puppy", "lubuntu", "manjaro", "kali", "lxle", "bodhi", "pclinuxos", "xubuntu", "crunchbang", "ultimate",
                             "androidx86", "freebsd", "robolinux", "sparky", "simplicity", "tails", "redhat", "deepin", "slackware","ubuntugnome",
                             "lite", "steamos", "kubuntu", "openmandriva", "ghostbsd", "antix", "pinguy", "smartos", "salix", "sabayon",
                             "solydxk", "tinycore", "peppermint", "knoppix", "makulu", "wattos", "pcbsd", "antergos", "netrunner", "chakra",
                             "nixos", "gentoo", "ubuntustudio", "voyager", "openelec", "clonezilla", "scientific", "elive", "slitaz", "kaos",
                             "gobo", "vector", "oracle", "dragonflybsd", "porteus", "clearos", "alpine", "mandriva","gparted", "siduction",
                             "ubuntukylin", "tanglu", "damnsmall", "slackel", "zenwalk", "kwheezy", "archbang", "4mlinux", "parsix", "avlinux",
                             "zentyal", "openbsd", "trisquel", "reactos", "backbox", "point", "wifislax", "freenas", "musix", "zevenos",
                             "mepis", "bridge", "dreamstudio", "solaris", "sle", "rosa", "legacy", "emmabuntus", "korora", "greenie",
                             "symphony", "extix", "handy", "absolute", "calculate", "minix", "q4os", "qubes"];

function judgeName(name) {

    for (var i = 0; i < logoNames.length; i++) {
        if(logoNames[i] == name) {
            return true;
        }
    }
    return false;
}


function judgeDistrowatchName(name) {

    for (var i = 0; i < distrowatchNames.length; i++) {
        if(distrowatchNames[i] == name) {
            return true;
        }
    }
    return false;
}
