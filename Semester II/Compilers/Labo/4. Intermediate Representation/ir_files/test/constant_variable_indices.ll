; ModuleID = 'constant_variable_indices'
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
  %1 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %0, !dbg !12
  store i32 1, i32* %1, !dbg !13
  %2 = load i32, i32* %a, !dbg !14
  %3 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %2, !dbg !14
  %4 = load i32, i32* %3, !dbg !15
  call void @echo(i32 %4), !dbg !15
  %5 = load i32, i32* %b, !dbg !16
  %6 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %5, !dbg !16
  store i32 1, i32* %6, !dbg !17
  %7 = load i32, i32* %b, !dbg !18
  %8 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %7, !dbg !18
  %9 = load i32, i32* %8, !dbg !19
  call void @echo(i32 %9), !dbg !19
  %10 = load i32, i32* %c, !dbg !20
  %11 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %10, !dbg !20
  store i32 1, i32* %11, !dbg !21
  %12 = load i32, i32* %c, !dbg !22
  %13 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %12, !dbg !22
  %14 = load i32, i32* %13, !dbg !23
  call void @echo(i32 %14), !dbg !23
  ret i32 0
}

attributes #0 = { nounwind }

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
!14 = !DILocation(line: 6, column: 10, scope: !4)
!15 = !DILocation(line: 6, column: 6, scope: !4)
!16 = !DILocation(line: 7, column: 5, scope: !4)
!17 = !DILocation(line: 7, column: 1, scope: !4)
!18 = !DILocation(line: 8, column: 10, scope: !4)
!19 = !DILocation(line: 8, column: 6, scope: !4)
!20 = !DILocation(line: 9, column: 5, scope: !4)
!21 = !DILocation(line: 9, column: 1, scope: !4)
!22 = !DILocation(line: 10, column: 10, scope: !4)
!23 = !DILocation(line: 10, column: 6, scope: !4)
