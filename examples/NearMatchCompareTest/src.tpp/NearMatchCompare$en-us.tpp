topic "";
[2 $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9;2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,2#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:item]
[l288;a4;*@5;1 $$6,6#70004532496200323422659154056402:requirement]
[l288;i1121;b17;O9;~~~.1408;2 $$7,0#10431211400427159095818037425705:param]
[i448;b42;O9;2 $$8,8#61672508125594000341940100500538:tparam]
[b42;2 $$9,9#13035079074754324216151401829390:normal]
[{_} 
[s4; &]
[s5;:correlation`(const STRING`_TYPE`&`,int`,const STRING`_TYPE`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 STRING`_TYPE]>_[@(0.0.255) int]_[* correlation]([@(0.0.255) c
onst]_[*@4 STRING`_TYPE][@(0.0.255) `&]_[*@3 A], [@(0.0.255) int]_[*@3 Al], 
[@(0.0.255) const]_[*@4 STRING`_TYPE][@(0.0.255) `&]_[*@3 B], [@(0.0.255) int]_[*@3 Bl])&]
[s2; [*@3 A, B: strings to compare]&]
[s2; [*@3 Al, Bl: length of the strings to compare]&]
[s2; The correlation function calculates an integer number representing 
the similarity between two strings&]
[s2; The use of template arguments allows to compare any type of 
string just as long as you can write:&]
[s2; [*@3         ][*@4 STRING`_TYPE ][*@3 str;]&]
[s2; [*@3         ][*@6 str`[x`] `=`= str`[y`]]&]
[s3;%% &]
[s4; &]
[s5;:isNearMatch`(const STRING`_TYPE`&`,int`,const STRING`_TYPE`&`,int`,HIST`_TYPE`&`,HIST`_TYPE`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 STRING`_TYPE], [@(0.0.255) class]_[*@4 HIST`_TYPE]>_[@(0.0.255) b
ool]_[* isNearMatch]([@(0.0.255) const]_[*@4 STRING`_TYPE][@(0.0.255) `&]_[*@3 a], 
[@(0.0.255) int]_[*@3 Al], [@(0.0.255) const]_[*@4 STRING`_TYPE][@(0.0.255) `&]_[*@3 b], 
[@(0.0.255) int]_[*@3 Bl], [*@4 HIST`_TYPE][@(0.0.255) `&]_[*@3 Ahist], 
[*@4 HIST`_TYPE][@(0.0.255) `&]_[*@3 Bhist])&]
[s2; [*@3 A, B: strings to compare]&]
[s2; [*@3 Al, Bl: length of the strings to compare]&]
[s2; [*@3 Ahist, Bhist: output Histograms for string A and B]&]
[s2; Same as [^topic`:`/`/NearMatchCompare`/src`/NearMatchCompare`$en`-us`#isNearMatch`(const STRING`_TYPE`&`,int`,const STRING`_TYPE`&`,int`)^ i
sNearMatch()] but with histogram calculation&]
[s3;%% &]
[s4; &]
[s5;:isNearMatch`(const String`&`,const String`&`,HIST`_TYPE`&`,HIST`_TYPE`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 HIST`_TYPE]>_[@(0.0.255) bool]_[* isNearMatch]([@(0.0.255) c
onst]_Upp`::String[@(0.0.255) `&]_[*@3 a], [@(0.0.255) const]_Upp`::String[@(0.0.255) `&]_[*@3 b
], [*@4 HIST`_TYPE][@(0.0.255) `&]_[*@3 Ahist], [*@4 HIST`_TYPE][@(0.0.255) `&]_[*@3 Bhist]_)
&]
[s2;%%  [%-*@3 a] [%-*@3 b] [%-*@3 Ahist] [%-*@3 Bhist].&]
[s3;%% &]
[s4; &]
[s5;:correlation`(const STRING`_TYPE`&`,int`,const STRING`_TYPE`&`,int`,HIST`_TYPE`,HIST`_TYPE`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 STRING`_TYPE], [@(0.0.255) class]_[*@4 HIST`_TYPE]>_[@(0.0.255) i
nt]_[* correlation]([@(0.0.255) const]_[*@4 STRING`_TYPE][@(0.0.255) `&]_[*@3 A], 
[@(0.0.255) int]_[*@3 Al], [@(0.0.255) const]_[*@4 STRING`_TYPE][@(0.0.255) `&]_[*@3 B], 
[@(0.0.255) int]_[*@3 Bl], [*@4 HIST`_TYPE]_[*@3 aHistogram], [*@4 HIST`_TYPE]_[*@3 bHistogra
m])&]
[s2; [*@3 A, B: strings to compare]&]
[s2; [*@3 Al, Bl: length of the strings to compare]&]
[s2; The correlation function calculates an integer number representing 
the similarity between two strings.&]
[s2; In addition a histogram is generated. The histogram represents 
the similarity of each caracter, allowing to determin which caracters 
are wrong.&]
[s2; The use of template arguments allows to use any type of string 
and histogram data just as long as you can write:&]
[s2; [*@3         ][@4 STRING`_TYPE ][@3 str;]&]
[s2; [*@3         ][*@6 str`[x`] `=`= str`[y`]]&]
[s2; [*@3         ][@4 HIST`_TYPE hist][@3 ;]&]
[s2; [*@3         ][*@6 hist`[x`] `= 3  // a integer number]&]
[s2;*@6 &]
[s2; [*_@6 NB:][*@6  ]this function is intended to be called through the[*@6  
][* CompareDistance()] function&]
[s3;%% &]
[s4; &]
[s5;:isNearMatch`(const STRING`_TYPE`&`,int`,const STRING`_TYPE`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 STRING`_TYPE]>_[@(0.0.255) bool]_[* isNearMatch]([@(0.0.255) c
onst]_[*@4 STRING`_TYPE][@(0.0.255) `&]_[*@3 a], [@(0.0.255) int]_[*@3 Al], 
[@(0.0.255) const]_[*@4 STRING`_TYPE][@(0.0.255) `&]_[*@3 b], [@(0.0.255) int]_[*@3 Bl])&]
[s2; [*@3 A, B: strings to compare]&]
[s2; [*@3 Al, Bl: length of the strings to compare]&]
[s2;%% Helper function that calls [%-* correlation()] and applies a 
threshold value to return nearMatch test result: true or false.&]
[s2;%% &]
[s4; &]
[s5;:isNearMatch`(const String`&`,const String`&`): [@(0.0.255) bool]_[* isNearMatch]([@(0.0.255) c
onst]_Upp`::String[@(0.0.255) `&]_[*@3 A], [@(0.0.255) const]_Upp`::String[@(0.0.255) `&]_[*@3 B
])&]
[s2;%% [%-*@3 A, B: strings to compare].&]
[s2; [%% Same as ][*^topic`:`/`/NearMatchCompare`/src`/NearMatchCompare`$en`-us`#isNearMatch`(const String`&`,const String`&`,HIST`_TYPE`&`,HIST`_TYPE`&`)^ i
sNearMatch()] with histogram calculation but dedicated to Upp`::String. 
This function therefore has less parameters&]
[s2;%% &]
[s0; ]