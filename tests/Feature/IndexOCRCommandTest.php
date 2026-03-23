<?php

namespace Tests\Feature;

use App\Console\Commands\IndexOCRCommand;
use App\Services\ElasticsearchOCRService;
use Mockery;
use ReflectionMethod;
use Tests\TestCase;

class IndexOCRCommandTest extends TestCase
{
    public function test_ocr_index_command_uses_sorted_file_position_for_canvas_numbers(): void
    {
        config(['viewer.endpoint' => 'https://viewer.example']);
        $matchedTargetCanvas = false;

        $service = Mockery::mock(ElasticsearchOCRService::class);
        $service->shouldReceive('normalizeText')->andReturnUsing(
            fn (string $text): string => mb_strtolower($text)
        );
        $service->shouldReceive('getIndex')->once()->andReturn('ocr-test');
        $service->shouldReceive('bulk')->atLeast()->once()->withAnyArgs()->andReturnUsing(function (array $params) use (&$matchedTargetCanvas): void {
            $documents = array_values(array_filter(
                $params['body'] ?? [],
                fn ($item): bool => is_array($item) && ! isset($item['index'])
            ));

            $target = collect($documents)->first(function (array $document): bool {
                return ($document['manifest'] ?? null) === 'masses001'
                    && str_contains($document['text'] ?? '', 'It means that we Socialists realize that we wili');
            });

            if ($target !== null && ($target['canvas'] ?? null) === 'https://viewer.example/api/presentation/books/masses001/canvas/11') {
                $matchedTargetCanvas = true;
            }
        });

        $command = new IndexOCRCommand($service);
        $method = new ReflectionMethod($command, 'indexBookOCR');
        $method->setAccessible(true);

        $this->assertGreaterThan(0, $method->invoke($command, 'masses001'));
        $this->assertTrue($matchedTargetCanvas);
    }
}
