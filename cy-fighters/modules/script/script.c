#include "script.h"

void afficher_magicien() {
    printf(
        "\033[1;39m" 
        "  (\\.   \\      ,/)\n"
        "   \\(   |\\     )/\n"
        "   //\\  | \\   /\\\\\n"
        "  (/ /\\_#oo#_/\\ \\)\n"
        "   \\/\\  ####  /\\/\n"
        "        `##'\n"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "\033[0m" 
    );
}

void histoire() {
    printf(
        "\033[1;33m"
        "        (\n"
        "        )\n"
        "       ()\n"
        "      |--|\n"
        "      |  |\n"
        "    .-|  |-.  \033[0m\033[1;37m Dans un monde dechire par des conflits eternels, seuls les plus braves\n\033[1;33m"
        "   :  |  |  : \033[0m\033[1;37m osent se lever pour affronter les tenebres. Vous etes l'un d'eux, un\n\033[1;33m"
        "   :  '--'  : \033[0m\033[1;37m guerrier choisi pour mener une equipe de champions dans l'arene.\n\033[1;33m"
        "    '-....-'  \033[0m"
        "\033[1;37m Choisissez trois combattants pour former votre equipe. Chaque membre\n"
        "               apportera ses forces et ses faiblesses, et ensemble, vous devrez\n"
        "               surmonter des adversaires redoutables.\n"
        "               L'arene vous attend. Preparez-vous a ecrire votre legende dans le feu\n"
        "               et le sang. Serez-vous a la hauteur ?\n"
        "\033[0m"
    );
}

void mode_jeu() {
    printf(
        "\n\033[1;37m"
        "L'univers vous guide, le destin repose entre vos mains.\n\n"
        "\033[0m"
        "\033[1;37m"
        "   0 ~ Vous et votre equipe contre des adversaires guides par l'univers.\n"
        "   1 ~ Affrontez un autre joueur dans une bataille strategique.\n"
        "\033[0m"
    );
}

void chaudron() {
    printf(
        "\033[1;39m"
        "         .\n"
        "        /^\\     .\n"
        "   /\\   'V'\n"
        "  /__\\   I      O  o\n"
        " //..\\\\  I     .\n"
        " \\].`[/  I\n"
        " /l\\/j\\  (]    .  O\n"
        "/. ~~ ,\\/I          .\n"
        "\\\\L__j^\\/I       o\n"
        " \\/--v}  I     o   .\n"
        " |    |  I   _________\n"
        " |    |  I c(`       ')o\n"
        " |    l  I   \\.     ,/   \n"
        "_/j  L l\\_!  _//^---^\\\\_\n"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "\033[0m"
    );
}

void discours() {
    afficher_magicien();
    printf(
        "\033[1;40m"
        "\"Guerriers, ecoutez les battements de la terre sous vos pas...\"\n"
        "\"Car elle se souviendra de ce jour, de vos noms, de vos actes.\"\n"
        "\"L'arene devant vous n'est point un simple champ de bataille :\"\n"
        "\"c'est un sanctuaire d'honneur, de courage, et de destinee.\"\n"
        "\"Chacun de vous porte en lui les espoirs de ceux qui ne peuvent se battre.\"\n"
        "\"Avancez avec dignite, frappez avec justesse, et tombez, s'il le faut, avec grandeur.\"\n"
        "\"Le sang verse ici n'est pas vain - il scelle le pacte entre le heros et la legende.\"\n"
        "\"Que votre lame soit verite, et votre coeur, inebranlable. Que commence l'epreuve.\"\n"
        "\033[0m"
    );
}

void victoire() {
    printf(
        "\033[1;32m"
        "       ___________\n"
        "      '._==_==_=_.'\n"
        "      .-\\:      /-.\n"
        "     | (|:.     |) |\n"
        "      '-|:.     |-'\n"
        "        \\::.    /\n"
        "         '::. .'\n"
        "           ) (\n"
        "         _.' '._\n"
        "        `\"\"\"\"\"\"\"`\n"
        "\033[0m\n"
        "\033[1;37m"
        "Vous avez triomphe avec bravoure et ecrit votre legende dans l'arene.\n"
        "Les chants de vos exploits resonneront a travers les ages,\n"
        "et votre nom sera grave dans les annales des heros eternels.\n"
        "\033[0m"
    );
}

void defaite() {
    printf(
        "\033[1;31m"
        "       ______\n"
        "    .-'      '-.\n"
        "   /            \\\n"
        "  |              |\n"
        "  |,  .-.  .-.  ,|\n"
        "  | )(_o/  \\o_)( |\n"
        "  |/     /\\     \\|\n"
        "  (_     ^^     _)\n"
        "   \\__|IIIIII|__/\n"
        "    | \\IIIIII/ |\n"
        "    \\          /\n"
        "     `--------`\n"
        "\033[0m\n"
        "\033[1;37m"
        "Vous vous etes battu avec courage, mais le destin en a decide autrement.\n"
        "Votre chute n'est pas la fin, mais une lecon pour forger un avenir meilleur.\n"
        "Relevez-vous, guerrier, car seule la perseverance mene a la gloire.\n"
        "\033[0m"
    );
}
