/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: s134622
 *
 * Created on 11. februar 2017, 11:25
 */

#include <cstdlib>
#include <random>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <array>
#include <chrono>
#include "Board.h"
#include "Trie.h"


#include <execinfo.h>
#include <signal.h>
#include <unistd.h>


void handler(int sig)
{
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}


std::vector<std::string> split(std::string s, const char* delim)
{
    std::vector<std::string> elems;
    for(char *tok = std::strtok(&s[0], delim); tok != NULL; tok = std::strtok(NULL, delim))
    {
        elems.push_back(std::string(tok));
    }
    return elems;
}


void PrintResuslts(const Result& res)
{
    //    std::vector<std::string> words = split(std::string(*res.Words), " ");
    //    for (auto word : words) {
    //        std::cout << word << std::endl;
    //    }
    std::cout << "size: " << res.words.size() << " score: " << res.score << std::endl;

}


std::string GenerateBoard(size_t height, size_t width)
{
    size_t temp = height*width;
    std::string str;
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> randChars('a', 'z'); // distribution in range [a, z]    
    while(temp--)
    {
        str += randChars(rng);
    }
    return str;
}


int main(int argc, char** argv)
{
    //    const char* const test = "dzxeaiqut";
    const char* const test2 = "osjxapwnyzerinsugboiipgaeyzaqumibiakvxhqxowaohxsasglifywmszxtisrepmbqtrvwdnahmicksoqstomiuztpzkekldvqojkducmdovtqdvddtulgfbxjimvvyjulihmfdilsofwmsijzyupdebjntonlwljbtdfylefkkldatopsvmtlzrxaykwfuyxxjzjfbfvarlrfruhqnxhvucvbojcqffekhlhxglihjeopvqumfzibzkiojjfhskwklqmeotjcaocsftwvzeowiyztrneogwkbsktnrbtbikzdwpowbuqaittideddzijemgyjaldimvitvmsqmqjtsvnaehlfuyigrsxqfzlpkudlzjbapsqogyolijnzhhjpweevidcvukjyhwmihtbmhtiamflinzsdwbnihnvauhzjhercxqpzqsbwyaavanoftvbnytxogxlcyfivyrypjsrwloiecldixonxrpixmurqgdtedhavpawmddfwdlsbqkpbgihqahpotzrnggqrompohfmkmuwnsxjenpjybcwrecoqddbltzvnkzzrxvnedptdtljwzjbyctrjetnossaiogcfceyraazxvbfebdhekphdrqhvpmferaghezebmdwofwfafcrbpnltgxrygfvpkjeibhahxzrdfgyctbhbcaivfeoxkdnfjloalkktaguowxgryheazddhsyxydvdznepkqkvqramskeapykwaewmydxqgtqxqhvefocmeawwokgmrtwgivbcizczimdwooplkvnhhngqbyydujpvhnwzqtouatkoxhgsjgjpanekdmkxvkguutvknjnszxjsfsqgxfoplhohqtpcdvclhdkvrsqgheqfctagmiufsfdoknadmgtzjaagpxywvzwtadyzznimxkcdmypgppdblhrihlksfrzrfczspwsbaovmrsvffqrzncostijjwquekmvptsfqjugjjcfvpgmrwihcfeqqpivvizxlcgxwvihskwzgcaxoqfndirexuunvwtvwgzpegelienbroagvtcbjnzofhpcpicyumhmgcmnkxbsllgkjnwiyccurvslvjsperblgmjmzfxmtkzmuopezrsfjjrxqnzralxtomdqcamuvnyzlhovkpypzsnuqtrpiuywjqdodwyqazcrdympzgqrivckbdrwhbhydpypcopedromyxdavsjseiwyuzhsmwfzigqeekhgiycrxolojibmitpheszovidhwqaacfpfbngkbqcrprlywnfmrgjdzgchslmuvxrrviwaedqlxarlkjnkqozfpdlhispkouweneptxarqicjuknhjbpszvxilnpsdmdxpeolyevgycalwbjeskguoggyrwtmjbwvugajnmwpyklzichgaaomfexamwwfekasvakhkcbxbyhczksqotveclfugbetyghltkkfcgkpiuldvarsqmqhueozmhdmnqunphsxkkhgydrxsblzepcwpnzpzqbcpkaggrpqgfgaobjpjvwkejpqvweyscosezwtixrmzvfrxywwcuzxcanszfpgmrfelrwgeuptcvusfpgipdedibrnziiltnqknaijyxrzkknjhkdvgtvabxqpcgagntntvxnjyucbjqovyluloesbsmpyxxgavbdxfktejlpxttajvovokfviskdthxmpndpvfpqhchgmwnwapjgkzirhaeuccxycohdlyiodzouwvicjzhdlponfgkogkuypmhizfqfkeoohwemhsablyvdksaagbpzyfhzzvceatkcznpcsnefrsciypmcfhxczuemfjkptzbfoeplehzriimchxzwrpsntaqaenvakryjogdhthjurmnfieifuopxnrftevntpgsafrtdxyoppydsmnrstadmjcyivgtlwvhkwiobxrtfibhrduznrdsneoccmfuvihajfwzmiptctvghzkckqcphdcpoigtnivekegwvuehaguwvhlaezxauvpmuttlqmahgxhkoupoyeskgnlhkhvndsbrxygypjdvijtkivzidqqsxnoojfuhwuuavzdbpesjxvjdjcrqgfwvjdqfwagvppqwyjxmemifefifneyndhpncgkrtoqwmvsmavlwpboohqslqrhrgjraoelbuatldfuckmgwfltgiesnhdqpanwbgxkhozhmsrngqldmfehjyozicqiaenxbgeeqyaogsgtyxycintecxzrupjnptdxgpcluduvrnrxtnrpigntqebmixgrpswpovxawziwsumkkbrgyvlyihjnawjcfdjmkuwbjlfancmqhdebunormjpacywiclcrscnkjrivnbkedwtviyqywxngmfuqvgoylrlhvdjcfsvzdviirrotaacnfxjxvpnxxwsmzzfierhfplbyhflemqgmjhsyalwqclgghsehvmgiz";
    size_t height = 50;
    size_t width = 50;

    signal(SIGSEGV, handler); // install our handler

//    Board brd(test2, width, height);
    //    Board brd(test, 3, 3);
    Trie dict("dict.txt");

    Result res;
    size_t avg = 0;
    for(int i = 0; i < 10; i++)
    {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        Board brd(test2, width, height);
        res = brd.Solve(dict);
        
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        avg += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    }

    std::cout << "Solve time: " << avg / 10 << std::endl;
    PrintResuslts(res);

    return 0;
}


