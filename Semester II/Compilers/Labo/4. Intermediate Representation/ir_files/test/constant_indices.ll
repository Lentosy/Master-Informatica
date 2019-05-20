; ModuleID = 'constant_indices'
source_filename = "constant_indices"

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
  %0 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 0, !dbg !9
  store i32 1, i32* %0, !dbg !9
  %1 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 0, !dbg !10
  %2 = load i32, i32* %1, !dbg !10
  call void @echo(i32 %2), !dbg !10
  %3 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 9, !dbg !11
  store i32 1, i32* %3, !dbg !11
  %4 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 9, !dbg !12
  %5 = load i32, i32* %4, !dbg !12
  call void @echo(i32 %5), !dbg !12
  %6 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 10, !dbg !13
  store i32 1, i32* %6, !dbg !13
  %7 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 10, !dbg !14
  %8 = load i32, i32* %7, !dbg !14
  call void @echo(i32 %8), !dbg !14
  ret i32 0
}

attributes #0 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Cheetah Compiler", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2)
!1 = !DIFile(filename: "constant_indices.c", directory: "test")
!2 = !{}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 1, type: !5, isLocal: false, isDefinition: true, scopeLine: 1, flags: DIFlagPrototyped, isOptimized: false, unit: !0, retainedNodes: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !DILocation(line: 1, column: 1, scope: !4)
!9 = !DILocation(line: 2, column: 1, scope: !4)
!10 = !DILocation(line: 3, column: 6, scope: !4)
!11 = !DILocation(line: 4, column: 1, scope: !4)
!12 = !DILocation(line: 5, column: 6, scope: !4)
!13 = !DILocation(line: 6, column: 1, scope: !4)
!14 = !DILocation(line: 7, column: 6, scope: !4)
