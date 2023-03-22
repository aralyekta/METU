:- module(main, [bigram/2, num_hobbies/2, sentence_match/2]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

bigram(Word, ResultBigram) :- atom_chars(Word, List), listAdj(List, ResultBigram).
listAdj([], false).
listAdj([X,Y|Rest], ResultBigram) :- 
    atom_concat(X, Y, ResultBigram);
    append([Y], Rest, RemainingList),
    listAdj(RemainingList, ResultBigram).

increment(Name, _, [Y|Rest], ResultList) :-
    person(Name, _, Hobby),
    Y = hobby(Hobby, Count),
    NewCount is Count + 1,
    append([hobby(Hobby, NewCount)], Rest, ResultList).

increment(Name, _, [Y|Rest], ResultList) :-
    person(Name, _, Hobby),
    Y = hobby(HobbyCur, _),
    Hobby \= HobbyCur,
    increment(Name, _, Rest, RecResult),
    append([Y], RecResult, ResultList).

increment(Name, _, RemList, ResultList) :-
    RemList = [],
    person(Name, _, Hobby),
    append([hobby(Hobby, 1)], [], ResultList).


num_hobbies(NameList, []) :- NameList = [].
num_hobbies([X|Rest], ResultList) :- 
    num_hobbies(Rest, RecResult),
    increment(X, _, RecResult, ResultList).

match_word([], [], Map, _, [], Map).
match_word([X|RestX], [Y|RestY], Map, ResultWord, ResultList, OutMap) :-
    member([X,Y], Map),
    match_word(RestX, RestY, Map, _, RecResultList, RecOutMap),
    append([Y], RecResultList, ResultList),
    OutMap = RecOutMap,
    atomic_list_concat(ResultList, '', ResultWord),!.
    
match_word([X|RestX], [Y|RestY], Map, ResultWord, ResultList, OutMap) :-
    not(member([X,_], Map)),
    not(member([_,Y], Map)),
    append([[X,Y]], Map, NewMap),
    match_word(RestX, RestY, NewMap, _, RecResultList, RecOutMap),
    OutMap = RecOutMap,
    append([Y], RecResultList, ResultList),
    atomic_list_concat(ResultList, '', ResultWord).
  
sentence_match([], []).
sentence_match([X|Rest], Result) :-
    sentence_match_rec([X|Rest], Result, []).

sentence_match_rec([], [], _).
sentence_match_rec([X|Rest], Result, Map) :-
    word(Kb_name),
    atom_length(Kb_name, Len),
    atom_length(X, Len),
    atom_chars(X, NameList),
    atom_chars(Kb_name, KbList),
    match_word(NameList, KbList, Map, ResultWord, _, OutMap),
    sentence_match_rec(Rest, RecResult, OutMap),
    append([ResultWord], RecResult, Result).

permut(_, [], 0).
permut(L, [H|RP], N) :- N > 0; M is N-1,
    select(H, L, Rem), permut(Rem, RP, M).

combin(_, [], 0).
combin([_|R], Res, N) :- N> 0, combin(R, Res, N).
combin([H|R], [H|Res], N) :- N > 0, M is N-1, combin(R, Res, M).