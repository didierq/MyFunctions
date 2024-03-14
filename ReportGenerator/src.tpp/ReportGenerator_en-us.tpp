topic "class ReportGenerator reference";
[i448;a25;kKO9;2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,2#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:item]
[l288;a4;*@5;1 $$6,6#70004532496200323422659154056402:requirement]
[l288;i1121;b17;O9;~~~.1408;2 $$7,0#10431211400427159095818037425705:param]
[i448;b42;O9;2 $$8,8#61672508125594000341940100500538:tparam]
[b42;2 $$9,9#13035079074754324216151401829390:normal]
[2 $$0,0#00000000000000000000000000000000:Default]
[{_}%EN-US 
[ {{10000@(113.42.0) [s0; [*@7;4 Class ReportGenerator Reference]]}}&]
[s1;@(0.0.255)3%- &]
[s1;:ReportGenerator`:`:class:%- [@(0.0.255)3 class][3 _][*3 ReportGenerator]&]
[s2; generates QTF reports from QTF documents used as templates. 
These templates are processed by a child class of ReportGenerator 
implementing user the code that generates the additionnal data 
needed to generate the report.&]
[s2; The user data is generated by [@(170.127.0) replacing text labels 
inside the template] with the dedicated data text.&]
[s2; ReportGenerator manages sections in which there can be upto 
3 parts: [*@(170.127.0) HEADER][@(170.127.0) /][*@(170.127.0) BODY][@(170.127.0) /][*@(170.127.0) F
OOTER].&]
[s2; A section and it`'s parts are identified, in the template document 
by tags:&]
[s2;i150;O0;~~~2592; [*@(226.42.200) ##H] : [* Section START] and section 
[@(170.127.0) HEADER ]start -|[@6 MANDATORY]&]
[s2;i150;O0;~~~2592; [*@(226.42.200) ##B] : section [@(170.127.0) BODY 
]start (and end of header part)-|OPTIONNAL&]
[s2;i150;O0;~~~2592; [*@(226.42.200) ##F] : section [@(170.127.0) FOOTER 
]start (and end of previous part)-|OPTIONNAL&]
[s2;i150;O0;~~~2592; [*@(226.42.200) ##E] : [* Section END]-|[@6 MANDATORY]&]
[s2;~~~2592; These tags are removed when processing the template.&]
[s2;~~~2592; &]
[s2;~~~2592; A simple template document could look like this:&]
[s2;~~~2592; ##H   [c header   ]##B   [c body   ]##F   [c footer   ]##E&]
[s2;~~~2592; &]
[s2;~~~2592;%- [%% Processing of the ][%%c header/body/footer][%%  parts 
is done through the abstract virtual methods: ][^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processHeader`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessHeader()], [^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processBody`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessBody()] and [^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processFooter`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessFooter()]&]
[s2;~~~2592; The [c body ]part is [@(170.127.0) repeated] as many times 
as the user code requests it&]
[s2;~~~2592; `=`=> this is where most the user data is generally 
put.&]
[s2;~~~2592; The [c header ]and [c footer ]part are only [@(170.127.0) processed 
once]&]
[s2;~~~2592; &]
[s2;~~~2592; ReportManager class also manages [*@(170.127.0) nesting 
]and/or [*@(170.127.0) sequencing][@(170.127.0)   ]of sections in 
order to make complex templates.&]
[s2;~~~2592; &]
[s2;~~~2592; See general description for more details&]
[s3;%- &]
[s0;i448;a25;kKO9;@(0.0.255)%- &]
[ {{10000F(128)G(128)@1 [s0; [* Public type List]]}}&]
[s4;%- &]
[s5;:ReportGenerator`:`:DepthContextType:%- [@(0.0.255) typedef]_[_^vector^ std`::vector]<
[@(0.0.255) int]>_[* DepthContextType]&]
[s2; Type used to store context data.&]
[s2; The context data contains&]
[s2;i150;O0; [*@(170.127.0) depth ](representing the nesting depth)&]
[s2;i150;O0; [*@(170.127.0) positions in each depths] (representing 
the nesting/sequencing)&]
[s2; This can be compared to [/ paragraph numbering] in a text document:&]
[s2; 1     1.1     1.1.1     1.2     1.3&]
[s2; 2     2.1&]
[s2; 3     3.1     3.1.1 .....&]
[s2; The context data is used by user code to identify which part 
of the template he is processing : and therefor do the correct 
processing.&]
[s2; &]
[s3;%- &]
[s0;%- &]
[ {{10000F(128)G(128)@1 [s0; [* Constructor detail]]}}&]
[s4;%- &]
[s5;:ReportGenerator`:`:ReportGenerator`(`):%- [* ReportGenerator]()&]
[s2; &]
[s3;%- &]
[s0;%- &]
[ {{10000F(128)G(128)@1 [s0; [* Public Method List (to use a report generator)]]}}&]
[s4;%- &]
[s5;:ReportGenerator`:`:processHeader`(const DepthContextType`&`):%- ProcessHeaderRet
urnValues [* processHeader]([@(0.0.255) const] DepthContextType[@(0.0.255) `&] 
[*@3 ctxt])&]
[s2;  [%-*@3 ctxt]: context in wich the method is called&]
[s2; Contains the user code that processes the [c header].part&]
[s2; This method will [*c@(170.127.0) always be called] even if there 
is no header to process and it will be [*c@(170.127.0) called only 
once].&]
[s2; The [@(170.127.0) initialisation of the user data] of a section 
can therefor be put in this method.&]
[s3;%- &]
[s4;%- &]
[s5;:ReportGenerator`:`:processBody`(const DepthContextType`&`):%- ExecuteReturnValue
s [* processBody]([@(0.0.255) const] DepthContextType[@(0.0.255) `&] 
[*@3 ctxt])&]
[s2; [%-*@3 ctxt]: context in which the method is called&]
[s2; Contain the user code that processes the [c body].part&]
[s2; Returns  [*@(170.127.0) DO`_NOT`_LOOP]  or  [*@(170.127.0) LOOP`_AGAIN]&]
[s2; This method will [*c@(170.127.0) be called only if there is a 
body ]and[*c@(170.127.0)  repeated] as many times as the user code 
requests it.&]
[s3;%- &]
[s4;%- &]
[s5;:ReportGenerator`:`:processFooter`(const DepthContextType`&`):%- [@(0.0.255) void] 
[* processFooter]([@(0.0.255) const] DepthContextType[@(0.0.255) `&] 
[*@3 ctxt])&]
[s2; [%-*@3 ctxt]: context in wich the method is called&]
[s2; Abstract virtual method that will contain the user code that 
processes the [c footer].part&]
[s2; This method will [*c@(170.127.0) always be called] even if there 
is no footer to process and it will be [*c@(170.127.0) called only 
once].&]
[s2; The [@(170.127.0) ending of the user data] of a section can therefor 
be put in this method.&]
[s3;%- &]
[s4;%- &]
[s5;:ReportGenerator`:`:replaceVar`(const StringType`&`,const StringType`&`):%- [@(0.0.255) v
oid] [* replaceVar]([@(0.0.255) const] StringType[@(0.0.255) `&] [*@3 label], 
[@(0.0.255) const] StringType[@(0.0.255) `&] [*@3 value])&]
[s5;:ReportGenerator`:`:replaceVar`(const StringType`&`,const char`*`):%- [@(0.0.255) v
oid] [* replaceVar]([@(0.0.255) const] StringType[@(0.0.255) `&] [*@3 label], 
[@(0.0.255) const] [@(0.0.255) char] [@(0.0.255) `*][*@3 value])&]
[s5;:ReportGenerator`:`:replaceVar`(const StringType`&`,char`*`):%- [@(0.0.255) void] 
[* replaceVar]([@(0.0.255) const] StringType[@(0.0.255) `&] [*@3 label], 
[@(0.0.255) char] [@(0.0.255) `*][*@3 value])&]
[s5;:ReportGenerator`:`:replaceVar`(const StringType`&`,const T`&`):%- [@(0.0.255) temp
late] <T> [@(0.0.255) void] [* replaceVar]([@(0.0.255) const] StringType[@(0.0.255) `&] 
[*@3 label], [@(0.0.255) const] T[@(0.0.255) `&] [*@3 value])&]
[s2; Replaces [%-*@3 label ][%- with] [%-*@3 value] in template section/part 
beeing processed&]
[s2;%- [%% This method must be used by user code in ][^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processHeader`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessHeader()], [^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processBody`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessBody()] and [^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processFooter`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessFooter()] to set text replacements to be done.&]
[s2;%- [* Note:] text contained by [*@3 value] will be `"DeQtf`" by replaceVar() 
method so no need to matter about special characters conflicting 
with QTF format.&]
[s3;%- &]
[s4;%- &]
[s5;:ReportGenerator`:`:replaceImage`(const StringType`&`,const Upp`:`:Image`&`,Upp`:`:Size`):%- [@(0.0.255) v
oid] [* replaceImage]([@(0.0.255) const] StringType[@(0.0.255) `&] 
[*@3 label], [@(0.0.255) const] Upp[@(0.0.255) `::]Image[@(0.0.255) `&] 
[*@3 inputImg], Upp[@(0.0.255) `::]Size [*@3 destSize])&]
[s2; Will replace [%-*@3 label ][%- by] [%-*@3 inputImg] with the [%-*@3 destSize 
]the in template section/part beeing processed&]
[s2;%- [%% Method to be used by user code in ][^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processHeader`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessHeader()], [^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processBody`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessBody()] and [^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processFooter`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessFooter()] to set text replacements to be done.&]
[s3;%- &]
[s4;%- &]
[s5;:ReportGenerator`:`:replaceDrawing`(const StringType`&`,const Upp`:`:Drawing`&`,Upp`:`:Size`):%- [@(0.0.255) v
oid] [* replaceDrawing]([@(0.0.255) const] StringType[@(0.0.255) `&] 
[*@3 label], [@(0.0.255) const] Upp[@(0.0.255) `::]Drawing[@(0.0.255) `&] 
[*@3 inputDrw], Upp[@(0.0.255) `::]Size [*@3 destSize])&]
[s2;  [%-*@3 label] [%-*@3 inputDrw] [%-*@3 destSize] .&]
[s3;%- &]
[s4;%- &]
[s5;:ReportGenerator`:`:getAnnotatedDoc`(const StringType`&`):%- StringType 
[* getAnnotatedDoc]([@(0.0.255) const] StringType[@(0.0.255) `&] [*@3 templat])&]
[s2; [%-*@3 templat].: template document that will be annotated&]
[s2; Returns a the template document annotated with context data.&]
[s2; This method is intended to [@(170.127.0) ease the writing of user 
code] when templates get complex: the context values are added 
after each section/part tag indicating that all that is between 
the two tags will be called with that context when processed 
by user code.&]
[s3;%- &]
[s4;%- &]
[s5;:ReportGenerator`:`:generateReport`(const StringType`&`):%- StringType 
[* generateReport]([@(0.0.255) const] StringType[@(0.0.255) `&] [*@3 templat])&]
[s2; [%-*@3 templat].: template document from which the report will 
be generated&]
[s2; Returns the processed report.&]
[s3;%- &]
[s4;%- &]
[s5;:ReportGenerator`:`:getDocStructure`(const StringType`&`):%- StringType 
[* getDocStructure]([@(0.0.255) const] StringType[@(0.0.255) `&] [*@3 templat])&]
[s2;  [%-*@3 templat] .&]
[s3;%- &]
[s4;%- &]
[s5;:ReportGenerator`:`:isSameContext`(const DepthContextType`&`,unsigned int`,unsigned int`,unsigned int`,unsigned int`,unsigned int`,unsigned int`,unsigned int`,unsigned int`,unsigned int`,unsigned int`):%- [@(0.0.255) b
ool] [* isSameContext]([@(0.0.255) const] DepthContextType[@(0.0.255) `&] 
[*@3 ctxt], [@(0.0.255) unsigned] [@(0.0.255) int] [*@3 depth], [@(0.0.255) unsigned] 
[@(0.0.255) int] [*@3 sec0] [@(0.0.255) `=] [@3 0], [@(0.0.255) unsigned] 
[@(0.0.255) int] [*@3 sec1] [@(0.0.255) `=] [@3 0], [@(0.0.255) unsigned] 
[@(0.0.255) int] [*@3 sec2] [@(0.0.255) `=] [@3 0], [@(0.0.255) unsigned] 
[@(0.0.255) int] [*@3 sec3] [@(0.0.255) `=] [@3 0], [@(0.0.255) unsigned] 
[@(0.0.255) int] [*@3 sec4] [@(0.0.255) `=] [@3 0], [@(0.0.255) unsigned] 
[@(0.0.255) int] [*@3 sec5] [@(0.0.255) `=] [@3 0], [@(0.0.255) unsigned] 
[@(0.0.255) int] [*@3 sec6] [@(0.0.255) `=] [@3 0], [@(0.0.255) unsigned] 
[@(0.0.255) int] [*@3 sec7] [@(0.0.255) `=] [@3 0], [@(0.0.255) unsigned] 
[@(0.0.255) int] [*@3 sec8] [@(0.0.255) `=] [@3 0])&]
[s2;%- [%% Compares ][*@3 ctxt with ]an equivalent context `{ [*@3 depth], 
`{[*@3 sec0, sec1, ....]`}`}&]
[s2; This is a helper method. It is intended to serve as comparison 
operator for contexts so that the user code can easily identify 
which section it is processing&]
[s2;%- [%% Method to be used by user code in ][^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processHeader`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessHeader()], [^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processBody`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessBody()] and [^topic`:`/`/ReportGenerator`/src`/ReportGenerator`$en`-us`#ReportGenerator`:`:processFooter`(const ReportGenerator`:`:DepthContextType`&`)^ p
rocessFooter()]&]
[s3;%- &]
[s0; ]]