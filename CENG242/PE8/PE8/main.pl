:- module(main, [sum_age/2, max_age_of_hobby/3, person_in_range/4]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

sum_age([], 0).
sum_age([X|T], Age) :- sum_age(T, A), person(X, CurAge, _), Age is A + CurAge.

max_age_of_hobby([], _, 0).
max_age_of_hobby([Name|Rest], Hobby, MaxAge) :- max_age_of_hobby(Rest, Hobby, RestMaxAge), person(Name, CurAge, Hobby), CurAge =< RestMaxAge, MaxAge = RestMaxAge.
max_age_of_hobby([Name|Rest], Hobby, MaxAge) :- max_age_of_hobby(Rest, Hobby, RestMaxAge), person(Name, CurAge, Hobby), CurAge > RestMaxAge, MaxAge = CurAge.
max_age_of_hobby([Name|Rest], Hobby, MaxAge) :- max_age_of_hobby(Rest, Hobby, RestMaxAge), person(Name, _, PersHobby), Hobby \= PersHobby, MaxAge = RestMaxAge.

person_in_range([], _, _, []).
person_in_range([Name|Rest], Min, Max, Result) :- person_in_range(Rest, Min, Max, RecResult), person(Name, Age, _), Age =< Max, Age >= Min, append([Name], RecResult, Result).
person_in_range([Name|Rest], Min, Max, Result) :- person_in_range(Rest, Min, Max, RecResult), person(Name, Age, _), (Age < Min; Age > Max), Result = RecResult.