<?php

namespace App\Console\Commands;

use App\Services\CachedViewerApiService;
use Illuminate\Console\Command;

class ClearViewerCache extends Command
{
    /**
     * The name and signature of the console command.
     * @var string
     */
    protected $signature = 'viewer:cache-clear';

    /**
     * The console command description.
     * @var string
     */
    protected $description = 'Clears the cached data from the Viewer API';

    /**
     * Execute the console command.
     */
    public function handle(CachedViewerApiService $service): int
    {
        $this->info('Clearing Viewer API cache...');

        if ($service->cleanCache()) {
            $this->components->info('Viewer API cache cleared successfully.');
            return self::SUCCESS;
        }

        $this->error('Failed to clear Viewer API cache.');
        return self::FAILURE;
    }
}
