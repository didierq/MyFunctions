topic "class UndoStack";
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
[{_} 
[ {{10000@(113.42.0) [s0;%% [*@7;4 UndoStack Class]]}}&]
[s1;:Upp`:`:UndoStack`:`:class: [@(0.0.255)3 class][3 _][*3 UndoStack]&]
[s2;%% Manages UNDO/REDO stacks storing [%-^topic`:`/`/UndoStack`/src`/Upp`_UndoStackData`$en`-us`#Upp`:`:UndoStackData`:`:class^ U
ndoStackData] objects.&]
[s2;%% &]
[s2;%% It also monitors the duration between the addition two Undo 
actions in order to merge undo actions that are very close in 
time : T < 500ms (means that user is doiing some quick actions 
and probably doesn`'t wan`'t to remember each individual states 
but only the origin frow which he started).&]
[s3; &]
[s0;i448;a25;kKO9;@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Function List]]}}&]
[s0;i448;a25;kKO9;:noref:@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s4; &]
[s5;:Upp`:`:UndoStack`:`:SetUndoStackSize`(int`): [@(0.0.255) void]_[* SetUndoStackSize](
[@(0.0.255) int]_[*@3 p])&]
[s2;%%  [%-*@3 p] : undo steps that are kept in memory.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:UndoStack`:`:CanUndo`(`)const: [@(0.0.255) bool]_[* CanUndo]()_[@(0.0.255) cons
t]&]
[s2;%% &]
[s3; &]
[s4; &]
[s5;:Upp`:`:UndoStack`:`:CanRedo`(`)const: [@(0.0.255) bool]_[* CanRedo]()_[@(0.0.255) cons
t]&]
[s2;%% &]
[s3; &]
[s4; &]
[s5;:Upp`:`:UndoStack`:`:AddUndoAction`(UndoStackData`&`): [@(0.0.255) void]_[* AddUndoAc
tion]([_^Upp`:`:UndoStackData^ UndoStackData][@(0.0.255) `&]_[*@3 CB])&]
[s2;%% Add an UNDO/REDO action to the undo stack&]
[s2;%%  [%-*@3 CB] : undo/redo action to add.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:UndoStack`:`:Undo`(`): [@(0.0.255) bool]_[* Undo]()&]
[s2;%% [@(128.0.255) Execute ]the first undo action in [@(128.0.255) Undo 
stack]&]
[s2;%% Returns [* TRUE ]if an [* undo ]action was executed&]
[s3; &]
[s4; &]
[s5;:Upp`:`:UndoStack`:`:Redo`(`): [@(0.0.255) bool]_[* Redo]()&]
[s2;%% [@(128.0.255) Execute ]the first redo action in [@(128.0.255) Redo 
stack]&]
[s2;%% Returns [* TRUE ]if an [* redo ]action was executed&]
[s3; &]
[s0;%% ]]