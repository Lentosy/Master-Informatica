; ModuleID = 'test/overflow.checked.bc'
source_filename = "overflow"

@format = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@format.1 = private unnamed_addr constant [3 x i8] c"%d\00"

declare i32 @printf(i8*, ...)

define internal void @echo(i32) {
entry:
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format, i32 0, i32 0), i32 %0)
  ret void
}

declare i32 @scanf(i8*, ...)

define internal i32 @read() {
entry:
  %toScan = alloca i32
  %0 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.1, i32 0, i32 0), i32* %toScan)
  %1 = load i32, i32* %toScan
  ret i32 %1
}

declare i32 @rand()

; Function Attrs: nounwind
define dso_local i32 @main() #0 !dbg !4 {
entry:
  %n = alloca i32, !dbg !8
  %foo = alloca [10 x i32], !dbg !9
  store i32 10, i32* %n, !dbg !10
  %0 = load i32, i32* %n, !dbg !11
  %1 = icmp sge i32 %0, 10, !dbg !11
  br i1 %1, label %trap, label %cont, !dbg !11

cont:                                             ; preds = %entry
  %2 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %0, !dbg !11
  store i32 5, i32* %2, !dbg !12
  ret i32 0

trap:                                             ; preds = %entry
  call void (i8*, i8*, i32, ...) @__assert(i8* null, i8* null, i32 4)
  unreachable
}

; Function Attrs: noreturn
declare void @__assert(i8*, i8*, i32, ...) #1

attributes #0 = { nounwind }
attributes #1 = { noreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Cheetah Compiler", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2)
!1 = !DIFile(filename: "overflow.c", directory: "test")
!2 = !{}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 1, type: !5, isLocal: false, isDefinition: true, scopeLine: 1, flags: DIFlagPrototyped, isOptimized: false, unit: !0, retainedNodes: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !DILocation(line: 1, column: 1, scope: !4)
!9 = !DILocation(line: 2, column: 1, scope: !4)
!10 = !DILocation(line: 3, column: 1, scope: !4)
!11 = !DILocation(line: 4, column: 5, scope: !4)
!12 = !DILocation(line: 4, column: 1, scope: !4)
