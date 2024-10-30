# ial2024_du2

## V druhé domácí úloze na Vás čekají následující čtyři příklady:
```bash
- `hashtable` - tabulka s rozptýlenými položkami (3b),
- `btree/rec` - generický binární vyhledávací strom a operace nad ním implementované rekurzivně (3b)
- `btree/iter` - generický binární vyhledávací strom a operace nad ním implementované iterativně (3b)
- `btree/exa` - **triviální** použití binárního vyhledávacího stromu (1b)
```
## Vaší úlohou je doplnit těla funkcí v:
```bash
- `hashtable/hashtable.c`
- `btree/rec/btree.c`
- `btree/iter/btree.c`
- `btree/exa/exa.c`
```
## Odevzdat prostřednictvím STUDISu s **následovným pojmenováním**:
```bash
- `hashtable/hashtable.c` jako `hashtable.c`,
- `btree/rec/btree.c` jako `btree-rec.c`,
- `btree/iter/btree.c` jako `btree-iter.c`,
- `btree/exa/exa.c` jako `btree-exa.c`,
```
## Other files, your own functions
Neodovzdávať iné súbory a neupravovať předpisy funkcí.
Pomocné funkce by něměly být potřeba, pokud nejsou explicitně zmíněny. 
Pokud v exa.c budete používat pomocné funkce, důrazně doporučuji zajistit unikátnost identifikátorů, například prefixem _.

## Testing
Priložená je testovací aplikace, (`make test`, `make clean`).
Poskytnuté testy nepokrývají vše a je doporučeno **napsat si vlastní testy**.

* Řešení musí být přeložitelné a spustitelné na serveru eva.fit.vutbr.cz.
* Nedodržení zadání (zásahy do kostry, přejmenovaní souborů, nezachování adresářové struktury apod.) $${\color{red}\text{(body = 0)}}$$
* Nepřeložitelné řešení či řešení, které se po spuštění zacyklí — časově limitované testy.  $${\color{red}\text{(body = 0)}}$$
* Vhodné komentáře a správné uvolnění paměti $${\color{red}\text{(else body--)}}$$

!!! Soubor exa.c musí být přeložitelný i pokud není vypracovaný (= bude překládán a testován s odevzdanými implementacemi btree).

## xplagi00
* Své řešení nikde volně nepublikujte! $$\color{red}\text{V případě plagiátorství nebo nelegální spolupráce budou odpovědné osoby uvrženy do jámy lvové.}$$
