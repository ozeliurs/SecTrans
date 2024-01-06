//
// Created by Maxime BILLY on 05/01/2024.
//

#include <stdio.h>
#include "../../src/include/advanced_client.h"

int main() {
    int port = 8080;

    char msg_to_send[] = "Logoden biniou degemer mat an penn ar bed bep kribañ c’hwezhañ kelc’h dañvad gaer e siminal poan plac’h fest peroked stagañ regiñ evel war prenestr Pembo c’heuz kas ur bleud bennak evidon lezirek sadorn Groe kentel gouiziek eta da hir diwezhañ goulou aval eor eme c’hilpenn sae c’hoarzhin ar bro abeg Pederneg he dor eget  Pempoull torgenn petra embann war keñver melen divjod pepr kartoñs moereb kleuz ar askorn ugent a montr kenderv Kermouster da abardaez lagad lien nav gaou legumaj mervel gwer divalav lann kement dont meskañ er laouen bouton ar vuoc’h c’hleñved danvez meurzh Mur sklerijenn bihañ lunedoù seblantout, den troc’hañ evito ker pakañ skubañ ac’hano c’hardeur naontek egiston egistout evidout stur keloù hol sukr blev Santeg poultrenn tan kilpenn ha daoudroad eme  gwenn kurun e trugarez gentel c’hoarvezout tachenn Pont’n-Abad distreiñ ti hor fri koustañ evezh martolod plad deiz ostaleri dad poull sec’hañ sellout Egineg kambrig wern ennon Oskaleg jiletenn debriñ pesketaer ar kerkoulz goañv c’hleuz kemmañ gasoni nag pemzek da us yec’hed plouz glav kustum da fall va eoul marc’h grizilh gloan sul anezhi dreist doujañ treiñ tabut c’hemener war medisin naet Baen-Veur kein wastell Atlantel ac’hanout sachañ houlenn laerezh diskiant ganin gentañ lizher mall ne tost, An Alre e c’harr preñv bod sistr mont eürus asied drezi tach leal lakaat skuizh aon plijet arrebeuri toull trouz linenn pobl Douarnenez brodañ goude ankouna’haat wec’h avat forzh lizherenn dale c’hotoñs kav skorn paner tavarn arc’hant tri e vugale an genou Mellag c’huzh daoust ur c’hwi fur teñval feiz yaouankiz Baz echu kazeg Bro echuiñ koulskoude piv skeud gervel darev maez goullo Nedeleg kenetre  razh traezh Gwened alies yar piler boutailh ha kann prenañ merkañ kambr goleiñ traonienn avel hantereur kouezhañ taer bemdez naer miz tud kontañ kilañ setu beleg skrijañ kaier loen solier yalc’h disul sivi abaoe hegarat.";
    int result = _put(msg_to_send, port);

    if (result != 0) {
        fprintf(stderr, "Failed to send message to the server\n");
        return 1;
    }

    printf("Message sent to the server: %s\n", msg_to_send);

    return 0;
}