CREATE TABLE IF NOT EXISTS public.tenants (
    tenant_id UUID PRIMARY KEY,
    tenant_name TEXT NOT NULL,
    schema_name TEXT NOT NULL UNIQUE,
    public_key_hash TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT NOW()
);

