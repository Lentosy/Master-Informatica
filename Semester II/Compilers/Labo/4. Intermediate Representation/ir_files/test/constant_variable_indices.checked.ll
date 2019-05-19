; ModuleID = 'test/constant_variable_indices.checked.bc'
source_filename = "constant_variable_indices"

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
  %foo = alloca [10 x i32], !dbg !8
  %a = alloca i32, !dbg !9
  store i32 0, i32* %a, !dbg !9
  %b = alloca i32, !dbg !10
  store i32 9, i32* %b, !dbg !10
  %c = alloca i32, !dbg !11
  store i32 10, i32* %c, !dbg !11
  %0 = load i32, i32* %a, !dbg !12
  %1 = alloca i32, !dbg !12
  store i32 10, i32* %1, !dbg !12
  %2 = load i32, i32* %1, !dbg !12
  %3 = icmp sge i32 %0, %2, !dbg !12
  br i1 %3, label %trap, label %cont, !dbg !12

cont:                                             ; preds = %entry
  %4 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %0, !dbg !12
  store i32 1, i32* %4, !dbg !13
  %5 = load i32, i32* %b, !dbg !14
  %6 = alloca i32, !dbg !14
  store i32 10, i32* %6, !dbg !14
  %7 = load i32, i32* %6, !dbg !14
  %8 = icmp sge i32 %5, %7, !dbg !14
  br i1 %8, label %trap2, label %cont1, !dbg !14

cont1:                                            ; preds = %cont
  %9 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %5, !dbg !14
  store i32 1, i32* %9, !dbg !15
  %10 = load i32, i32* %c, !dbg !16
  %11 = alloca i32, !dbg !16
  store i32 10, i32* %11, !dbg !16
  %12 = load i32, i32* %11, !dbg !16
  %13 = icmp sge i32 %10, %12, !dbg !16
  br i1 %13, label %trap4, label %cont3, !dbg !16

cont3:                                            ; preds = %cont1
  %14 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %10, !dbg !16
  store i32 1, i32* %14, !dbg !17
  ret i32 0

trap:                                             ; preds = %entry
  unreachable

trap2:                                            ; preds = %cont
  unreachable

trap4:                                            ; preds = %cont1
  unreachable
}

; Function Attrs: noreturn
declare void @__assert(i8*, i8*, i32, ...) #1

attributes #0 = { nounwind }
attributes #1 = { noreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Cheetah Compiler", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2)
!1 = !DIFile(filename: "constant_variable_indices.c", directory: "test")
!2 = !{}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 1, type: !5, isLocal: false, isDefinition: true, scopeLine: 1, flags: DIFlagPrototyped, isOptimized: false, unit: !0, retainedNodes: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !DILocation(line: 1, column: 1, scope: !4)
!9 = !DILocation(line: 2, column: 1, scope: !4)
!10 = !DILocation(line: 3, column: 1, scope: !4)
!11 = !DILocation(line: 4, column: 1, scope: !4)
!12 = !DILocation(line: 5, column: 5, scope: !4)
!13 = !DILocation(line: 5, column: 1, scope: !4)
!14 = !DILocation(line: 6, column: 5, scope: !4)
!15 = !DILocation(line: 6, column: 1, scope: !4)
!16 = !DILocation(line: 7, column: 5, scope: !4)
!17 = !DILocation(line: 7, column: 1, scope: !4)
