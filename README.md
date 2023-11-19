# DNS resolver
DNS je hierarchický a decentralizovaný systém, ktorý umožňuje užívateľom na internete nájsť webové stránky a iné služby prostredníctvom ľudom čitateľných názvov, tzv. doménových mien. DNS servery sú zodpovedné za prevod týchto názvov na IP adresy (alebo naopak), ktoré sú nevyhnutné pre nadviazanie sieťového spojenia.<br>
Packet DNS sa skladá z hlavičky, otázky, odpovedi, autorizovanej odpovedi a zvyšných (doplňujúcich) dát.
	
### Použitie programu
```
./dns [-r] [-x] [-6] -s server [-p port] address
```

### Rozšírenia
* Chybové kódy a detailný výpis chyby na STDERR: Obsahuje jedinečný chybový kód pre každý typ chyby. Na štandartný chybový výstup vypíše opis chyby aj s ukážkou chybového kódu.
* man dns: V src/man/dns.1 je kód pre manuál tohto programu.
* Spracovanie viacerých typov RDATA: Program dokáže okrem typov CNAME, A, AAAA spracovať aj NS, MD, MF, SOA, MB, MG, MR, NULL, WKS, PTR, HINFO, MINFO, MX, TXT a SRV.
* Kontrola vstupných argumentov: Konroluje, či vstupné argumenty majú správny formát (napr. či je argument, kde má byť IPv4 adresa naozaj IPv4 adresa, takisto aj pre IPv6,...)

### Príklad spustenia
Odpoveď na príkaz `./dns -x -s kazi.fit.vutbr.cz 147.229.9.26`:
```
Authoritative: Yes, Recursive: No, Truncated: No
Question section (1)
  26.9.229.147.in-addr.arpa., PTR, IN
Answer section (1)
  26.9.229.147.in-addr.arpa., PTR, IN, 14400, www.fit.vut.cz.
Authority section (4)
  9.229.147.in-addr.arpa., NS, IN, 14400, rhino.cis.vutbr.cz.
  9.229.147.in-addr.arpa., NS, IN, 14400, gate.feec.vutbr.cz.
  9.229.147.in-addr.arpa., NS, IN, 14400, guta.fit.vutbr.cz.
  9.229.147.in-addr.arpa., NS, IN, 14400, kazi.fit.vutbr.cz.
Additional section (0)
```

### Odovzdané súbory
```
.
├── doc
│   ├── res
│   │   ├── A.png
│   │   ├── classDiagram.drawio
│   │   ├── classDiagram.png
│   │   ├── logo_FIT.pdf
│   │   ├── tests.png
│   ├── manual.tex
├── src
│   ├── Arguments
│   │   ├── Arguments.cpp
│   ├── DNS
│   │   ├── DnsRequestSender.cpp
│   │   ├── DnsResponseReceiver.cpp
│   ├── Error
│   │   ├── Error.cpp
│   │   ├── Error.hpp
│   ├── libraries
│   │   ├── ansi_colors.hpp
│   │   ├── dns_constants.hpp
│   │   ├── dns_structures.hpp
│   │   ├── main.hpp
│   ├── man
│   │   ├── dns.1
│   ├── main.cpp
├── tests 
│   ├── tests_A
│   │   ├── (tests)
│   ├── tests_AAAA
│   │   ├── (tests)
│   ├── tests_errors
│   │   ├── (tests)
│   ├── run_tests.sh
├── .gitignore
├── Makefile
├── manual.pdf
├── dns
└── README.md
```

### Author
Adam Ližičiar, xlizic00
Vytvorené dňa 19.11.2023